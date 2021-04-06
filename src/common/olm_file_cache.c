#include "olm_file.h"
#include "olm_file_cache.h"
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <linux/limits.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <sys/stat.h>

/*****************************************************************************/
// structs

/**
 * Recursively free olm file cache struct. Shoud be called under lock.
 * @param current Pointer to current item in link list.
 */
static void
olm_file_cache_free_rec(struct olm_file_index_t *current) {
    if (current == NULL)
        return;
    else if (current->next != NULL)
        olm_file_cache_free_rec(current->next);

    olm_file_free(current->data);
    free(current);
}

/**
 * Recursively insert a new olm file to link list. Shoud be called under lock.
 * @param current Pointer to current item in link list, cannot be NULL.
 * @param new Pointer to new olm file to add to link list.
 * @return 0 if already in list, 1 on successfully added, or negative errno on failure.
 */
static int
olm_file_cache_insert_rec(struct olm_file_index_t **index, 
                       struct olm_file_index_t *new) {
    struct olm_file_index_t *current = *index;
    int r = 1;

    if (new == NULL || new->data == NULL) { // invalid args
        r = -EINVAL;
    } else if (current == NULL) { // add to tail
        *index = new;
        new->next = NULL; // just in case
    } else if (strncmp(current->data->name, new->data->name,
                strlen(new->data->name)+1) == 0) { // file already in list
        r = 0;
    } else if (current->data->unix_time > new->data->unix_time) { // insert
        new->next = current;
        *index = new;
    } else { // recursion
        r = olm_file_cache_insert_rec(&current->next, new);
    }

    return r;
}

/**
 * Recursively add new olm file to link list. Shoud be called under lock.
 * @param in The file cache.
 * @param new_file New olm file to add to link list.
 * @return 0 on success or negative errno on failure.
 */
static int
olm_file_cache_insert(olm_file_cache_t *in, olm_file_t *new_file) {
    struct olm_file_index_t *new_index;
    int r = 0;

    if (in == NULL || new_file == NULL)
        return -EINVAL;

    if ((new_index = malloc(sizeof(struct olm_file_index_t))) == NULL)
        return -ENOMEM;

    new_index->next = NULL;
    new_index->data = new_file;

    if ((r = olm_file_cache_insert_rec(&in->files, new_index)) >= 0) {
        // recursively add
        in->len += r;
        r = 0;
    } else { // error, cleanup from malloc
        free(new_index);
    }

    return r;
}

static int 
olm_file_cache_remove_rec(struct olm_file_index_t **index, char *filename) {
    struct olm_file_index_t *current = *index;
    int r = 0;

    if (index == NULL || current == NULL) {
        r = -EINVAL;
    } else if (strncmp(current->data->name, filename,
                strlen(filename)+1) == 0) { // file found, remove it from list
        *index = current->next;
        olm_file_free(current->data);
        free(current);
    } else { // recursion
        r = olm_file_cache_remove_rec(&current->next, filename);
    }

    return r;
}


/*****************************************************************************/
// public functions

int
olm_file_cache_new(char *dir_path, olm_file_cache_t **out) {
    olm_file_cache_t *new_cache;
    char dir_abs_path[PATH_MAX];
    struct dirent *dir;
    char temp_path[PATH_MAX];
    olm_file_t *new_olm_file;
    struct stat st;
    DIR *d;
    int r = 0;

    if (realpath(dir_path, dir_abs_path) == NULL)
        return -EINVAL;

    if (dir_abs_path[strlen(dir_abs_path)] != '/') {
        dir_abs_path[strlen(dir_abs_path)] = '/';
        dir_abs_path[strlen(dir_abs_path)+1] = '\0';
    }

    if ((new_cache = malloc(sizeof(olm_file_cache_t))) == NULL)
        return -ENOMEM;

    new_cache->dir = NULL;
    new_cache->files = NULL;
    new_cache->len = 0;
    pthread_mutex_init(&new_cache->mutex, NULL);

    // set dir name
    if ((new_cache->dir = malloc(strlen(dir_abs_path)+1)) == NULL) {
        free(new_cache);
        return -ENOMEM;
    }
    strncpy(new_cache->dir, dir_abs_path, strlen(dir_abs_path)+1);

    if ((d = opendir(dir_path)) != NULL) { // add all existing file to linked list
        while ((dir = readdir(d)) != NULL) { // directory found
            if (strncmp(dir->d_name, ".", sizeof(dir->d_name)) == 0 ||
                    strncmp(dir->d_name, "..", sizeof(dir->d_name)) == 0)
                continue; // skip . and ..

            sprintf(temp_path, "%s%s", new_cache->dir, dir->d_name);

            // check for empty files
            stat(temp_path, &st);
            if (st.st_size == 0) {
                remove(temp_path);
                continue;
            }

            r = olm_file_new(temp_path, &new_olm_file);
            if (r == -ENOMEM) { // out of memory
                break;
            } else if (r != 0) { // invalid olm file, delete it
                remove(temp_path);
                continue;
            } 

            if ((r = olm_file_cache_insert(new_cache, new_olm_file)) != 0) {
                olm_file_free(new_olm_file);
                break;
            }
        }
        closedir(d);
    } else {
        r = -ENOENT;
    }

    if (r == 0)
        *out = new_cache;
    else // something failed 
        olm_file_cache_free(new_cache);

    return r;
}

void
olm_file_cache_free(olm_file_cache_t *in) {
    if (in == NULL)
        return;

    // don't care about locks with the data struct is being freed

    if (in->dir != NULL) {
        free(in->dir);
        in->dir = NULL;
    }

    if (in->files != NULL) {
        olm_file_cache_free_rec(in->files);
        in->files = NULL;
    }

    free(in);
}

int
olm_file_cache_add(olm_file_cache_t *in, char *filepath) {
    char new_filepath[PATH_MAX];
    olm_file_t *new_file = NULL;
    int r = 0;

    if ((r = olm_file_new(filepath, &new_file)) != 0)
        return r;

    // move file
    sprintf(new_filepath, "%s%s", in->dir, basename(filepath));
    if ((r = rename(filepath, new_filepath)) == 0) {
        pthread_mutex_lock(&in->mutex);
        r = olm_file_cache_insert(in, new_file);
        pthread_mutex_unlock(&in->mutex);
    } 

    if (r != 0 && new_file != NULL)
        olm_file_free(new_file);

    return r;
}

int
olm_file_cache_remove(olm_file_cache_t *in, char *filename) {
    char temp_path[PATH_MAX];
    int r;


    sprintf(temp_path, "%s%s", in->dir, filename);
    if ((r = remove(temp_path)) != 0)
        return -EINVAL; // file not in cache

    pthread_mutex_lock(&in->mutex);
    if ((r = olm_file_cache_remove_rec(&in->files, filename)) == 0) // remove from list
        --in->len;
    pthread_mutex_unlock(&in->mutex);

    return r;
}

int
olm_file_cache_index(olm_file_cache_t *in, int index, const char *keyword,
        olm_file_t **out) {
    char filepath[PATH_MAX];
    size_t len;
    struct olm_file_index_t *current;
    int r = 0;

    len = olm_file_cache_len(in, keyword);
    if ((size_t)index >= len)
        return -EINVAL;

    pthread_mutex_lock(&in->mutex);

    size_t i=0;
    for (current = in->files; current != NULL && i <= len; current = current->next) {
        if (keyword != NULL && strncmp(current->data->keyword,
                    keyword, strlen(keyword)+1) != 0)
            continue;

        if (i == (size_t)index) {
            sprintf(filepath, "%s%s", in->dir, current->data->name);
            r = olm_file_new(filepath, out);
            break; // index was found, no need to continue
        }

        ++i;
    }

    pthread_mutex_unlock(&in->mutex);
    return r;
}

uint32_t
olm_file_cache_len(olm_file_cache_t *in, const char *keyword) {
    struct olm_file_index_t *current;
    uint32_t len = 0;

    pthread_mutex_lock(&in->mutex);

    if (keyword == NULL || in == NULL || in->files == NULL) { // No filter / no list
        len = in->len;
    } else { // filter by keyword
        for (current = in->files; current != NULL && current->data != NULL; 
                current = current->next) {
            if (current->data == NULL)
                break;
            else if (strncmp(current->data->keyword, keyword, strlen(keyword)+1) == 0)
                ++len;
        }
    }

    pthread_mutex_unlock(&in->mutex);
    return len;
}

bool
olm_file_cache_file_exist(olm_file_cache_t *in, const char *filename) {
    struct olm_file_index_t *current;
    bool r = false;

    pthread_mutex_lock(&in->mutex);

    for (current = in->files; current != NULL && current->data != NULL;
            current = current->next)
        if (strncmp(current->data->name, filename, strlen(filename)+1) == 0) {
            r = true;
            break;
        }

    pthread_mutex_unlock(&in->mutex);
    return r;
}

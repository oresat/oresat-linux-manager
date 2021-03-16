#include "olm_file.h"
#include "olm_file_cache.h"
#include <errno.h>
#include <libgen.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void
olm_file_free(olm_file_t *out) {
    if (out == NULL)
        return;

    if (out->name != NULL)
        free(out->name);

    if (out->board != NULL)
        free(out->board);

    if (out->keyword != NULL)
        free(out->keyword);

    if (out->extension != NULL)
        free(out->extension);

    free(out);
}

int
olm_file_new(char *filepath, olm_file_t **out) {
    char *unix_time_str, *end;
    char filename[PATH_MAX];
    olm_file_t *new_file = NULL;
    int keyword_loc = 0, date_loc = 0, ext_loc = 0;
    int len, r = 0;
    struct stat st;

    if (filepath == NULL)
        return -EINVAL;

    // also test if the filepath is valid
    if ((r = stat(filepath, &st)) != 0)
        return r;

    strncpy(filename, basename(filepath), strlen(basename(filepath))+1);

    // find all '_' locations and the start of the extension (the 1st '.')
    for (int i=0; i<strlen(filename); ++i) {
        if (filename[i] == '_') { // find keyword and data locs
            if (keyword_loc == 0) {
                keyword_loc = i+1; // add 1 to not include '_'
            } else if (date_loc == 0) {
                date_loc = i+1; // add 1 to not include '_'
            } else {
                // both keyword and date have been found, there are extra '_'
                r = -EINVAL;
                break; 
            }
        } else if (filename[i] == '.') { // find optional extension loc
            ext_loc = i;
            break; // found extension
        }
    }

    if (keyword_loc == 0 || date_loc == 0 || r != 0)
        return -EINVAL; // not all manitory '_' locs were found or invalid filename

    if ((new_file = malloc(sizeof(olm_file_t))) == NULL)
        goto olm_file_mem_error;

    new_file->size = st.st_size;
    new_file->name = NULL;
    new_file->board = NULL;
    new_file->keyword = NULL;
    new_file->extension = NULL;

    // copy filename
    if ((new_file->name = malloc(strlen(filename)+1)) == NULL)
        goto olm_file_mem_error;
    strncpy(new_file->name, filename, strlen(filename)+1);

    // copy board name
    len = keyword_loc;
    if ((new_file->board = malloc(len)) == NULL)
        goto olm_file_mem_error;
    strncpy(new_file->board, filename, len);
    new_file->board[len-1] = '\0';
    
    // copy get keyword 
    len = date_loc - keyword_loc;
    if ((new_file->keyword = malloc(len)) == NULL)
        goto olm_file_mem_error;
    strncpy(new_file->keyword, &filename[keyword_loc], len);
    new_file->keyword[len-1] = '\0';

    // copy unix time
    len = (ext_loc == 0 ? strlen(filename) + 1 : ext_loc) - date_loc + 1;
    if ((unix_time_str = malloc(len)) == NULL)
        goto olm_file_mem_error;
    strncpy(unix_time_str, &filename[date_loc], len);
    unix_time_str[len-1] = '\0';
    new_file->unix_time = (uint32_t)strtol(unix_time_str, &end, 10);
    free(unix_time_str);

    // copy extension (if there is one)
    if (ext_loc != 0) {
        len = strlen(filename) - ext_loc + 2;
        if ((new_file->extension = malloc(len)) == NULL)
            goto olm_file_mem_error;
        strncpy(new_file->extension, &filename[ext_loc], len);
        new_file->extension[len-1] = '\0';
    }

    *out = new_file;
    return r;

    olm_file_mem_error:
    r = -ENOMEM;
    olm_file_free(new_file);
    return r;
}

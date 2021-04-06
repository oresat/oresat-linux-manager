/**
 * Utility functions.
 *
 * @file        utility.c
 * @ingroup     utility
 *
 * This file is part of OreSat Linux Manager, a common CAN to Dbus interface
 * for daemons running on OreSat Linux boards.
 * Project home page is <https://github.com/oresat/oresat-linux-manager>.
 */

#include "utility.h"
#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

#define COPY_BUFF_LEN 1024

int
copyfile(const char *src, const char *dest) {
    char buf[COPY_BUFF_LEN];
    FILE *r_fptr = NULL;
    FILE *w_fptr = NULL;
    size_t bytes;
    int r = 0;

    if (dest == NULL || src == NULL)
        return -EINVAL;
    
    errno = 0;
    if ((r_fptr = fopen(src, "r")) == NULL) {
        r = -errno;
        goto copy_error;
    }

    errno = 0;
    if ((w_fptr = fopen(dest, "w")) == NULL) {
        r = -errno;
        goto copy_error;
    }

    while (!feof(r_fptr)) {
        if ((bytes = fread(buf, 1, COPY_BUFF_LEN, r_fptr)))
            fwrite(buf, 1, bytes, w_fptr);
    }

    fclose(r_fptr);
    fclose(w_fptr);

    return r;

copy_error:

    FCLOSE(r_fptr);
    FCLOSE(w_fptr);
    return r;
}

int
mkdir_path(const char *path, mode_t mode) {
    char temp_path[PATH_MAX];
    int r = 0;

    if (path == NULL)
        return -EINVAL;

    // start on 1 to skip 1st '/' in absolut path
    for (size_t i=1; i<=strlen(path) && i<PATH_MAX-1; ++i) {
        if (path[i] == '/' || i == strlen(path)) {
            strncpy(temp_path, path, i);
            temp_path[i] = '\0';

            if (is_dir(temp_path))
                continue; // dir already exist

            if ((r = mkdir(temp_path, mode)) != 0)
                break;
        }
    }

    return r;
}

bool
is_file(const char *path) {
    FILE *fptr;
    bool r = false;

    if ((fptr = fopen(path, "r")) != NULL) {
        fclose(fptr);
        r = true;
    }

    return r;
}

bool
is_dir(const char* path) {
    DIR* dir = NULL;
    bool r = false;

   if ((dir = opendir(path)) != NULL) {
        closedir(dir);
        r = true;
    }

    return r;
}

int
clear_dir(const char *path) {
    char filepath[PATH_MAX];
    struct dirent *dir;
    DIR *d;
    int r = 0;

    if ((d = opendir(path)) != NULL) { // add all existing file to list
        while((dir = readdir(d)) != NULL) { // directory found
            if (strncmp(dir->d_name, ".", sizeof(dir->d_name)) == 0 ||
                    strncmp(dir->d_name, "..", sizeof(dir->d_name)) == 0)
                continue; // skip . and ..

            if (path[strlen(path)-1] == '/') // path ends with a '/'
                sprintf(filepath, "%s%s", path, dir->d_name);
            else // need a '/' at end of path
                sprintf(filepath, "%s/%s", path, dir->d_name);

            if ((r = remove(filepath)) != 0)
                break; // remove failed
        }
        closedir(d);
    } else {
        r = -ENOENT;
    }

    return r;
}

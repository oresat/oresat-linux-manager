#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

#define FREE(data) \
if (data != NULL) \
    free(data);

#define FREE_AND_NULL(data) \
if (data != NULL) { \
    free(data); \
    data = NULL; \
}

#define FCLOSE(data) \
if (data != NULL) \
    fclose(data);


#define MALLOC_AND_STRNCPY(out, in) \
if ((out = malloc(strlen(in)+1)) == NULL) \
    strncpy(out, in, strlen(in)+1);

#define MALLOC_STRNCPY_OR_GOTO(out, in, goto_label) \
MALLOC_AND_STRNCPY(out, in) \
else \
    goto goto_label;

#define MALLOC_AND_MEMCPY(out, in) \
if ((out = malloc(sizeof(in))) == NULL) \
    memcpy(out, in, sizeof(in));

#define MALLOC_MEMCPY_OR_GOTO(out, in, goto_label) \
MALLOC_AND_MEMCPY(out, in) \
else \
    goto goto_label;

/**
 * @brief Copies a file.
 *
 * @param src Source file path.
 * @param dest Destination file path.
 *
 * @return 0 on success or negative errno on error.
 */
int copyfile(const char *src, const char *dest);

/**
 * @breif Makes directory path. A wrapper on top of mkdir().
 *
 * @param path Directory path to make.
 * @param mode Directory mode.
 *
 * @return 0 on success or negative errno on error.
 */
int mkdir_path(const char *path, mode_t mode);

/**
 * @breif Check to see if file exist.
 *
 * @param path File to check.
 *
 * @return true if the file exist or false if file does not exist.
 */
bool is_file(const char *path);

/**
 * @breif Check to see if directory exist.
 *
 * @param path Directory to check.
 *
 * @return true if the directory exist or false if directory does not exist.
 */
bool is_dir(const char *path);

/**
 * @breif Delete all files in a directory.
 *
 * @param path Directory to clear.
 *
 * @return 0 on success or negative errno on error.
 */
int clear_dir(const char *path);

#endif /* UTILITY_H */

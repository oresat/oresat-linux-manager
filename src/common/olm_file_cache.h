#ifndef OLM_FILE_CACHE_H
#define OLM_FILE_CACHE_H

#include "olm_file.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

/** Link list index for the file cache list. */
struct olm_file_index_t {
    /** Next olm file */
    struct olm_file_index_t *next;
    /** OLM file meta data */
    olm_file_t *data;
};

/**
 * OLM file cache data. Should be treated as readonly outside
 * olm_file_cache_* functions.
 */
typedef struct {
    /** The absolute path to the cache. */
    char *dir;
    /** The link list of files in the cache. Will be order oldest to newest. */
    struct olm_file_index_t *files;
    /** The length of lenght files link list for convenience */
    uint32_t len;
    /** Mutex for accessing data */
    pthread_mutex_t mutex;
} olm_file_cache_t;

/**
 * @brief Create a new olm_file_t cache.
 *
 * @param dir_path The directory to use.
 * @param out The new file cache.
 *
 * @return 0 on success or negative errno on failure.
 */
int olm_file_cache_new(char *dir_path, olm_file_cache_t **out);

/**
 * @brief Clean up olm_file_cache_t struct.
 *
 * @param in The file cache.
 */
void olm_file_cache_free(olm_file_cache_t *in);

/**
 * @brief Add new file to olm file cache.
 *
 * @param in The file cache.
 * @oaram filename Path to a new file to add.
 *
 * @return 0 on success or negative errno on failure.
 */
int olm_file_cache_add(olm_file_cache_t *in, char *filename);

/**
 * @brief Removes a file from olm file cache.
 *
 * @param in The file cache.
 * @param filename The name of the file to delete.
 *
 * @return 0 on success or negative errno on failure.
 */
int olm_file_cache_remove(olm_file_cache_t *in, char *filename);

/**
 * @brief Get a copy of the olm_file_t at a index. Can be used for sepecific
 * keywords too.
 *
 * @param in The file cache.
 * @param index The index in the list wanted.
 * @param keyword The olm keyword to filter with. Set to NULL, if no filter
 * is wanted.
 * @param out Th copy of olm file data at the index. Must be freed with @ref
 * olm_file_free.
 *
 * @return 0 on success or negative errno on failure.
 */
int olm_file_cache_index(olm_file_cache_t *in, int index, const char *keyword,
                         olm_file_t **out);

/**
 * @brief Get the length of the file cahe. Can be used for sepecific keywords
 * too.
 *
 * @param in The file cache.
 * @param keyword The olm keyword to filter with. Set to NULL, if no filter
 * is wanted.
 *
 * @return The length of the cache.
 */
uint32_t olm_file_cache_len(olm_file_cache_t *in, const char *keyword);

/**
 * @brief check if file exist in cache
 *
 * @return true if the file is the cache or false if not
 */
bool olm_file_cache_file_exist(olm_file_cache_t *in, const char *filename);

#endif /* OLM_FILE_CACHE_H */

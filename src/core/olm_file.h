#ifndef OLM_FILE_H
#define OLM_FILE_H

#include <stdint.h>

// format: board_keyword_unix-time.extension
// example1: gps_update_1612726568.tar.xz
// example2: star-tracker_test_1612726568

/** The meta date in olm filename format. */
typedef struct {
    /** The full filename. */
    char *name;
    /** The board the file was sent to or is from. */
    char *board;
    /** The unique keyword. */
    char *keyword;
    /** The unix time when the file was made. */
    uint32_t unix_time;
    /** The extension for the file. */
    char *extension;
    /** The size of the file. */
    uint32_t size;
} olm_file_t;

/**
 * @brief A convience function for creating olm_file structf from a filename.
 * Must be freed with olm_file_free().
 * @param The filename
 * @param out A pointer to a new olm_file struct if successful.
 * @return 0 on success or a negative errno on failure.
 */
int olm_file_new(char *filename, olm_file_t **out);

/**
 * @brief Free a olm_file_t struct. Will free the pointer.
 * @param file The olm_file struct to free.
 */
void olm_file_free(olm_file_t *file);

#endif /* OLM_FILE_H */

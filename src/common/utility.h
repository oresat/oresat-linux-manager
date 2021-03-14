#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <string.h>

#define FREE(data) \
if (data != NULL) \
    free(data); \

#define FREE_AND_NULL(data) \
if (data != NULL) { \
    free(data); \
    data = NULL; \
}

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

#endif /* UTILITY_H */

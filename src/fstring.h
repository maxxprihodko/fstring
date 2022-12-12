#ifndef _FSTRING_H
#define _FSTRING_H

#include <stdint.h>
#include <stdbool.h>

/* Amount of bytes the string will grow by in each reallocation. */
#define CHUNK_SIZE 20

/* Main string representation used within the library. */
typedef struct fstring {
    /* Total bytes of space allocated */
    int32_t space;

    /* Total bytes of space used */
    int32_t used;

    /* String of characters */
    char *value;

    /* Amount of bytes our string will grow by */
    int32_t grow_by;
} fstring_t;

void fstring_init(fstring_t *s, int32_t amount);
void fstring_free(fstring_t *s);
char *fstring_get(fstring_t *s);
void fstring_add_char(fstring_t *s, char c);
void fstring_add_string(fstring_t *s, const char* str);
fstring_t fstring_substring(fstring_t *s, int32_t start, int32_t length);
void fstring_append(fstring_t *dest, fstring_t *src);
bool fstring_contains(fstring_t *s, const char *val);

#endif

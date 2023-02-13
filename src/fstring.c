#include "fstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* string_init() - initializes an empty string instance
 *      args: string instance, amount to grow by
 *      returns: none
 *
 * Grows by CHUNK_SIZE if `amount` is 0
 */
void fstring_init(fstring_t *s, int amount)
{
    s->value = NULL;
    s->space = s->used = 0;
    s->grow_by = (amount > 0 ? amount : CHUNK_SIZE);
}

/* fstring_free() - frees a flexible string instance */
void fstring_free(fstring_t *s)
{
    /* Avoid pointless frees */
    if (s->value)
        free(s->value);
}

/* fstring_get() - gets the string contained in the flex string
 *      args: instance
 *      returns: pointer to characters
 */
char *fstring_get(fstring_t *s)
{
    /* First make sure there's room for the '\0' */
    if (s->used == s->space) /* string is full, add room for one more char */
        s->value = realloc(s->value, ++s->space);

    /* Add terminating '\0'.  Don't increment fs_used -- the '\0' is not part of
     * the string, and shouldn't be counted if someone wants to continue adding
     * characters to the string later.
     */
    s->value[s->used] = '\0';

    /* Now return the (terminated) string. */
    return s->value;
}

/* fstring_add_char() - appends a character to the flexible string
 *      args: instance, character to append
 *      returns: none
 */
void fstring_add_char(fstring_t *s, char c)
{
    /* If we haven't allocated memory yet use malloc() */
    if (s->space == 0) {
        /* Signify that we have allocated space and are ready to add to the
         * string */
        s->value = malloc(s->grow_by);
        s->used = 0;
        s->space = s->grow_by;
    } else if (s->used + 1 >= s->space) { /* used + 1 for \0 */
        /* We don't have an empty string and we need to allocate more space so
         * use realloc() */
        s->space += s->grow_by;
        s->value = realloc(s->value, s->space);
    }

    s->value[s->used++] = c;
}

/* fstring_add_string() - appends a string to the flexible string
 *      args: instance, string to append
 *      returns: none
 */
void fstring_add_string(fstring_t *s, const char *str)
{
    int32_t c;

    /* Add each character by calling add char */
    while ((c = *str++) != '\0')
        fstring_add_char(s, c);
}

/* fstring_substring() - extracts a section of a flex string
 *      args: instance, start position, length
 *      returns: substring
 */
fstring_t fstring_substring(fstring_t *s, int32_t start, int32_t length)
{
    fstring_t new = {length + 1, length, malloc(length + 1), CHUNK_SIZE};

    /* Loop through each character and copy it over */
    int32_t c = 0;
    int32_t end = start + length;
    for (start; start < end; start++)
        new.value[c++] = s->value[start];

    return new;
}

/* fstring_append() - appends a flex string to another flex string
 *      args: destination, source
 *      returns: none
 */
void fstring_append(fstring_t *dest, fstring_t *src)
{
    /* Ensure that we have valid values before we attempt to append them
     * together. */
    if (dest->value && src->value)
        fstring_add_string(dest, fstring_get(src));
}

/* fstring_contains() - searches for a string within a flex string
 *      args: flex string, value
 *      returns: true if `s` contains `val`
 */
bool fstring_contains(fstring_t *s, const char *val)
{
    /* Save the string as we need it for later */
    const char *str = fstring_get(s);
    size_t len = strlen(val);

    for (size_t start = 0, end = s->used - len - 1; end <= s->used;
         end += ++start) {
        /* Compare the new substring with the string we are searching for */
        for (int i = start; i <= end; i++) {
            /* If any characters are not identical, break */
            if (str[i] != val[i - start])
                break;
            /* We know that str[i] == val[i] */
            if (i == end)
                return true;
        }
    }

    return false;
}

/* fstring_empty() - returns true if string is empty
 *      args: flex string
 *      returns: true if empty
 */
bool fstring_empty(fstring_t *s) { return s->used == 0; }

/* fstring_clear() - 'clears' a flex string
 *      args: flex string
 *      returns: none
 */
void fstring_clear(fstring_t *s)
{
    /* If string isn't empty set the first character to '\0'. Total space
     * allocated will stay the same */
    if (s->used) {
        s->used = 0;
        s->value[0] = '\0';
    }
}
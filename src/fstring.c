#include "fstring.h"

#include <stdlib.h>
#include <stdio.h>
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
void fstring_free(fstring_t *s) { free(s->value); }

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
void fstring_add_string(fstring_t *s, const char* str)
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
    fstring_t new;
    
    /* Allocate space for our new string (+1 for \0) */
    new.value = malloc(length + 1);
    new.grow_by = CHUNK_SIZE;
    new.used = length;
    new.space = length + 1;

    /* Loop through each character and copy it over */
    int32_t c = 0;
    int32_t end = start + length;
    for (start; start < end; start++)
        new.value[c++] = s->value[start];
    
    return new;
}
# fstring
A simple flexible string manipulation library. The goal of this library is to make it much easier to manipulate strings in C. I have provided a short codeblock that demonstrates how this library could be used.

```c
#include "fstring.h"

int main(int argc, char **argv) 
{
  fstring_t s;
  fstring_init(&s, 0);
  
  fstring_add_string(&s, "Hello, world!");
  printf("%s", fstring_get(&s));
  
  fstring_free(&s);
  return 0;
}
```

## Documentation
```c
/* string_init() - initializes an empty string instance
 *      args: string instance, amount to grow by
 *      returns: none
 *
 * Grows by CHUNK_SIZE if `amount` is 0
 */
void fstring_init(fstring_t *s, int amount)
```
<br/>

```c
/* fstring_free() - frees a flexible string instance */
void fstring_free(fstring_t *s)
```
<br/>

```c
/* fstring_get() - gets the string contained in the flex string
 *      args: instance
 *      returns: pointer to characters
 */
char *fstring_get(fstring_t *s)
```
<br/>

```c
/* fstring_add_char() - appends a character to the flexible string
 *      args: instance, character to append
 *      returns: none
 */
void fstring_add_char(fstring_t *s, char c)
```
<br/>

```c
/* fstring_add_string() - appends a string to the flexible string
 *      args: instance, string to append
 *      returns: none
 */
void fstring_add_string(fstring_t *s, const char* str)
```
<br/>

```c
/* fstring_substring() - extracts a section of a flex string 
 *      args: instance, start position, length
 *      returns: substring
 */
fstring_t fstring_substring(fstring_t *s, int32_t start, int32_t length)
```
<br/>

```c
/* fstring_contains() - searches for a string within a flex string
 *      args: flex string, value
 *      returns: true if `s` contains `val`
 */
bool fstring_contains(fstring_t *s, const char *val)
```
<br/>

```c
/* fstring_empty() - returns true if string is empty
 *      args: flex string
 *      returns: true if empty
 */
bool fstring_empty(fstring_t *s)
```
<br/>

```c
/* fstring_clear() - 'clears' a flex string
 *      args: flex string
 *      returns: none
 */
void fstring_clear(fstring_t *s)
```

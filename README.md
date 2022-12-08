# Stringlib
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
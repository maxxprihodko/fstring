# Stringlib
A simple flexible string manipulation library. The goal of this library is to make it much easier to manipulate strings in C. I have composed simple documentation below on how to correctly use the current functions. I will update these functions as I develop the library.

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

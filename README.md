# fstring ![workflow](https://github.com/maxxprihodko/fstring/actions/workflows/c-cpp.yml/badge.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
A lightweight flexible string library that makes it incredibly easy to manipulate strings in C. The goal of fstring is to bring all of the modern features strings have to C while keeping a simple and compact codebase.

```c
#include "fstring.h"

int main(int argc, char **argv) 
{
  fstring_t s = fstring_new(0);
  
  fstring_add_string(&s, "Hello, world!");
  printf("%s", fstring_get(&s));
  
  fstring_free(&s);
  return 0;
}
```
Documentation for the functions can be found [here](docs/functions.md)

#define CTEST_MAIN

#include "../src/fstring.h"
#include "ctest.h"

int main(int argc, char **argv)
{
    ctest_main(argc, (const char **)argv);
    return 0;
}

CTEST_DATA(fstring)
{
    fstring_t s;
    fstring_t n;
};

CTEST_SETUP(fstring)
{
    fstring_init(&data->s, 0);
    fstring_init(&data->n, 0);
};

CTEST_TEARDOWN(fstring)
{

    fstring_free(&data->s);
    fstring_free(&data->n);
};

CTEST2(fstring, add_char)
{
    fstring_add_char(&data->s, 'A');
    ASSERT_STR("A", fstring_get(&data->s));
};

CTEST2(fstring, add_string)
{
    fstring_add_string(&data->s, "some string");
    ASSERT_STR("some string", fstring_get(&data->s));
};

CTEST2(fstring, substring)
{
    fstring_add_string(&data->s, "Hello, world!");

    data->n = fstring_substring(&data->s, 0, 5);
    ASSERT_STR("Hello", fstring_get(&data->n));

    data->n = fstring_substring(&data->s, 3, 4);
    ASSERT_STR("lo, ", fstring_get(&data->n));
};

CTEST2(fstring, append)
{
    fstring_add_string(&data->n, "value");
    fstring_add_string(&data->s, "some ");

    fstring_append(&data->s, &data->n);
    ASSERT_STR("some value", fstring_get(&data->s));
};

CTEST2(fstring, contains)
{
    fstring_add_string(&data->s, "Word");

    ASSERT_EQUAL(true, fstring_contains(&data->s, "Wo"));
    ASSERT_EQUAL(true, fstring_contains(&data->s, "or"));
    ASSERT_EQUAL(true, fstring_contains(&data->s, "rd"));
    
    ASSERT_EQUAL(false, fstring_contains(&data->s, "xx"));
};
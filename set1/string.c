#include "string.h"

/*
 * allocate and return a pointer to a String given a char array and its length
 *
 * must be freed by caller!
 */
String *make_string(char *s, size_t len)
{
    String *string = (String*)malloc(sizeof(String));
    string->s = s;
    string->len = len;
    return string;
}


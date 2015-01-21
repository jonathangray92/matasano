#include <string.h>
#include "string.h"

/*
 * allocate and return a pointer to a String given a char array and its length
 *
 * must be freed by caller!
 */
String *make_string_bytes(char *s, size_t len)
{
    String *string = (String*)malloc(sizeof(String));
    string->s = s;
    string->len = len;
    return string;
}

/*
 * allocate and return a pointer to a String given a null-terminated char array
 *
 * must be freed by caller!
 */
String *make_string(char *s)
{
    String *string = (String*)malloc(sizeof(String));
    string->s = s;
    string->len = strlen(s);
    return string;
}

/*
 * Return a string of "size" characters, each initialized to "byte"
 *
 * Must be freed by caller!
 */
String *make_string_of_byte(char byte, size_t size)
{
    char *s = (char*)malloc(size);
    for (int i = 0; i < size; i++) {
        s[i] = byte;
    }
    String *string = (String*)malloc(sizeof(String));
    string->s = s;
    string->len = size;
    return string;
}

/*
 * Frees the internal char array, and then frees the string struct
 */
void free_string(String *string)
{
    free(string->s);
    free(string);
}

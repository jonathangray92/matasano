#ifndef __STRING_H__
#define __STRING_H__

#include <stdlib.h>

/*
 * string struct includes char array and length
 */
typedef struct {
    char *s;
    size_t len;
} String;

/*
 * allocate and return a pointer to a String given a byte array and its length
 *
 * must be freed by caller!
 */
String *make_string_bytes(char*, size_t);

/*
 * allocate and return a pointer to a String given a null-terminated char array
 *
 * must be freed by caller!
 */
String *make_string(char*);

/*
 * Return a string of "size" characters, each initialized to "byte"
 */
String *make_string_of_byte(char byte, size_t size);

/*
 * Frees the internal char array, and then frees the string struct
 */
void free_string(String *string);

#endif

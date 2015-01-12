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
 * allocate and return a pointer to a String given a char array and its length
 *
 * must be freed by caller!
 */
String *make_string(char*, size_t);

#endif

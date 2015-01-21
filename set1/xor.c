#include "string.h"
#include "xor.h"

/*
 * Given two strings of equal length, return their XOR combination
 *
 * If the strings are not equal in length, return NULL
 */
String* fixed_xor(String *s1, String *s2)
{
    // check that sizes are equal
    if (s1->len != s2->len) {
        return NULL;
    }

    // allocate an output string
    char *output = (char*)malloc(s1->len);

    // compute the xor byte-by-byte
    for (int i = 0; i < s1->len; i++) {
        output[i] = s1->s[i] ^ s2->s[i];
    }

    // return result as String struct
    return make_string_bytes(output, s1->len);
}

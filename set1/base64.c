#include <stdlib.h>
#include <stdio.h>
#include "base64.h"

/*
 * Allowed base64 chars, in order
 */
const char BASE64_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char BASE64_PAD = '='; 

/*
 * convert bytes in a group of 3 (a, b, c) to four groups of 6 bytes
 */
#define GROUP_0(a) ((a) >> 2)
#define GROUP_1(a,b) ((((a) & 0x3) << 4) | (((b) & 0xf0) >> 4))
#define GROUP_2(b,c) ((((b) & 0xf) << 2) | ((c) & 0x3))
#define GROUP_3(c) ((c) & 0x3f)

/*
 * convert "length" raw bytes to null-terminated base64 string
 */
char* encode_base64(char* bytes, int length)
{
    // allocate output array
    int base64_length = BASE64_LENGTH(length);
    char *base64 = (char*)malloc(base64_length);

    // handle three bytes at a time (produces 4 base64 chars)
    // N.B. "i" is the index of the bytes array
    // N.B. "j" is the index of the base64 array
    int i, j;
    for (i = 0, j = 0; i < length - PADDING_LENGTH(length); i += 3, j += 4) {
        // get 3 octets
        unsigned char b0 = bytes[i];
        unsigned char b1 = bytes[i+1];
        unsigned char b2 = bytes[i+2];

        // perform base64 character lookup and write to output
        base64[j]   = BASE64_CHARS[GROUP_0(b0)];
        base64[j+1] = BASE64_CHARS[GROUP_1(b0, b1)];
        base64[j+2] = BASE64_CHARS[GROUP_2(b1, b2)];
        base64[j+3] = BASE64_CHARS[GROUP_3(b2)];
    }

    // handle padding characters
    // if 0 bytes left, we're done!
    int bytes_left = PADDING_LENGTH(length);

    // if 1 byte left, pad second char with 0, and add "=="
    if (bytes_left == 1) {
        // get last byte
        unsigned char b0 = bytes[length-1];

        // write two b64 chars and two padding chars
        base64[j]   = BASE64_CHARS[GROUP_0(b0)];
        base64[j+1] = BASE64_CHARS[GROUP_1(b0, 0)];
        base64[j+2] = BASE64_PAD;
        base64[j+3] = BASE64_PAD;

    // if 2 bytes left, pad third char with 0, and add "="
    } else if (bytes_left == 2) {
        // get last two bytes
        unsigned char b0 = bytes[length-2];
        unsigned char b1 = bytes[length-1];

        // write down three b64 chars and one padding char
        base64[j]   = BASE64_CHARS[GROUP_0(b0)];
        base64[j+1] = BASE64_CHARS[GROUP_1(b0, b1)];
        base64[j+2] = BASE64_CHARS[GROUP_2(b1, 0)];
        base64[j+3] = BASE64_PAD;
    }

    return base64;
}

/*
 * convert base64 string with "length" chars to raw bytes
 */
char* decode_base64(char* base64, int base64_length)
{
    return NULL;
}

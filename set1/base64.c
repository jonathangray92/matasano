#include <stdlib.h>
#include <stdio.h>
#include "base64.h"
#include "string.h"

/*
 * forward declared functions
 */
unsigned char base64_decode_char(unsigned char);

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
String* encode_base64(String* bytes)
{
    // allocate output array (+1 for null byte)
    int base64_length = BASE64_LENGTH(bytes->len);
    int padding_length = PADDING_LENGTH(bytes->len);
    char *base64 = (char*)malloc(base64_length + 1);

    // handle three bytes at a time (produces 4 base64 chars)
    // N.B. "i" is the index of the bytes array
    // N.B. "j" is the index of the base64 array
    int i, j;
    for (i = 0, j = 0; i < bytes->len - padding_length; i += 3, j += 4) {
        // get 3 octets
        unsigned char b0 = bytes->s[i];
        unsigned char b1 = bytes->s[i+1];
        unsigned char b2 = bytes->s[i+2];

        // perform base64 character lookup and write to output
        base64[j]   = BASE64_CHARS[GROUP_0(b0)];
        base64[j+1] = BASE64_CHARS[GROUP_1(b0, b1)];
        base64[j+2] = BASE64_CHARS[GROUP_2(b1, b2)];
        base64[j+3] = BASE64_CHARS[GROUP_3(b2)];
    }

    // handle padding characters
    // if 0 bytes left, we're done!
    // if 1 byte left, pad second char with 0, and add "=="
    if (padding_length == 1) {
        // get last byte
        unsigned char b0 = bytes->s[bytes->len - 1];

        // write two b64 chars and two padding chars
        base64[j]   = BASE64_CHARS[GROUP_0(b0)];
        base64[j+1] = BASE64_CHARS[GROUP_1(b0, 0)];
        base64[j+2] = BASE64_PAD;
        base64[j+3] = BASE64_PAD;

    // if 2 bytes left, pad third char with 0, and add "="
    } else if (padding_length == 2) {
        // get last two bytes
        unsigned char b0 = bytes->s[bytes->len - 2];
        unsigned char b1 = bytes->s[bytes->len - 1];

        // write down three b64 chars and one padding char
        base64[j]   = BASE64_CHARS[GROUP_0(b0)];
        base64[j+1] = BASE64_CHARS[GROUP_1(b0, b1)];
        base64[j+2] = BASE64_CHARS[GROUP_2(b1, 0)];
        base64[j+3] = BASE64_PAD;
    }

    // allocate and return String struct
    return make_string(base64, base64_length);
}

/*
 * convert base64 string to raw bytes
 */
String* decode_base64(String *base64)
{
    // if not a multiple of 4 base64 characters, throw an error
    if (base64->len % 4 != 0) {
        return NULL;
    }

    // get number of padding characters
    int padding_size;
    if (base64->s[base64->len - 2] == BASE64_PAD) {
        padding_size = 2;
    } else if (base64->s[base64->len - 1] == BASE64_PAD) {
        padding_size = 1;
    } else {
        padding_size = 0;
    }

    // calculate length of the byte string, and allocate memory
    // 4 base64 chars => 3 bytes
    int bytes_length = (base64->len / 4) * 3 - padding_size;
    char *bytes = (char*)malloc(bytes_length);

    // handle all but the last 4 (handled separately because of padding)
    //
    // N.B. "i" is the index of the bytes array
    // N.B. "j" is the index of the base64 array
    int i, j;
    for (i = 0, j = 0; j < base64->len; i += 3, j += 4) {
        // get base64 characters
        unsigned char base64_0 = base64->s[j];
        unsigned char base64_1 = base64->s[j+1];
        unsigned char base64_2 = base64->s[j+2];
        unsigned char base64_3 = base64->s[j+3];

        // get 6-bit groupings 
        unsigned char g0 = base64_decode_char(base64_0);
        unsigned char g1 = base64_decode_char(base64_1);
        unsigned char g2 = base64_decode_char(base64_2);
        unsigned char g3 = base64_decode_char(base64_3);

        // fit into three bytes and write to bytes array
        // if we have reached padding characters, then write nothing
        bytes[i] = (g0 << 2) | (g1 >> 4);
        if (base64_2 != BASE64_PAD) {
            bytes[i+1] = (g1 << 4) | (g2 >> 2);
        }
        if (base64_3 != BASE64_PAD) {
            bytes[i+2] = (g2 << 6) | g3;
        }
    }

    // add null terminator
    bytes[bytes_length] = 0;

    // construct a string struct and return a pointer to it
    return make_string(bytes, bytes_length);
}

/*
 * convert a base64 character to its 6-bit representation
 *
 * ASSUMES that the input is a valid character. Treats padding as 0.
 */
unsigned char base64_decode_char(unsigned char b64_char)
{
    if (b64_char >= 'A' && b64_char <= 'Z') {
        return b64_char - 'A';
    } else if (b64_char >= 'a' && b64_char <= 'z') {
        return b64_char - 'a' + 26;
    } else if (b64_char >= '0' && b64_char <= '9') {
        return b64_char - '0' + 52;
    } else if (b64_char == '+') {
        return 62;
    } else if (b64_char == '/') {
        return 63;
    } else {
        return 0;
    }
}

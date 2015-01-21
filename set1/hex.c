#include <stdlib.h>
#include <stdio.h>
#include "hex.h"

/*
 * Allowed hex chars, in order
 */
const char HEX_CHARS[] = "0123456789abcdef";

/*
 * convert raw bytes to null-terminated hex string
 */
String* encode_hex(String *bytes)
{
    // two hex chars per byte
    int hexlength = 2 * bytes->len;

    // allocate output string (plus null suffix)
    char *hex = (char*)malloc(hexlength + 1);

    // convert via array lookup
    for (int i = 0; i < hexlength; i++) {
        unsigned char byte = bytes->s[i];
        unsigned char upper = (byte >> 4) & 0xf;
        unsigned char lower = byte & 0xf;
        hex[2*i] = HEX_CHARS[upper];
        hex[(2*i)+1] = HEX_CHARS[lower];
    }

    // add null termination
    hex[hexlength] = 0;

    return make_string(hex);
}

/*
 * convert hex string to raw bytes
 */
String* decode_hex(String* hex)
{
    // don't allow dangling nibbles
    // user must be decoding an integer number of bytes
    if (hex->len & 1) return NULL;

    // two hex chars per byte
    int bytes_length = hex->len / 2;

    // allocate output string
    char *bytes = (char*)malloc(bytes_length);

    // convert via ascii arithmetic
    for (int i = 0; i < bytes_length; i++) {
        char hex_upper = hex->s[2*i];
        char hex_lower = hex->s[(2*i)+1];
        char byte = 0;

        // convert upper hex char 
        if (hex_upper >= '0' && hex_upper <= '9') {
            byte |= (hex_upper - '0') << 4;
        } else if (hex_upper >= 'a' && hex_upper <= 'f') {
            byte |= (hex_upper - 'a' + 10) << 4;
        } else {
            free(bytes);
            return NULL;
        }

        // convert lower hex char 
        if (hex_lower >= '0' && hex_lower <= '9') {
            byte |= (hex_lower - '0');
        } else if (hex_lower >= 'a' && hex_lower <= 'f') {
            byte |= (hex_lower - 'a' + 10);
        } else {
            free(bytes);
            return NULL;
        }

        // write byte to output array
        bytes[i] = byte;
    }

    return make_string_bytes(bytes, bytes_length);
}

#ifndef __BASE64_H__
#define __BASE64_H__

#include "string.h"

/*
 * Number of padding characters in the base64 encoding of x octets
 */
#define PADDING_LENGTH(x) ((x) % 3)

/*
 * Length of base64 encoding of x octets
 *
 * Each three bytes correspond to four base64 characters. Dangling bytes
 * are padded to a group of three bytes, and the last PADDING_LENGTH characters
 * will be padding character
 *
 * e.g. BASE64_LENGTH(4) is two groups of three when padded => 8 base64 chars
 */
#define BASE64_LENGTH(x) ((((x) + 2) / 3) * 4)

/*
 * convert raw bytes to base64 string
 */
String* encode_base64(String *bytes);

/*
 * convert base64 string with "length" chars to raw bytes
 */
String* decode_base64(String *base64);

#endif

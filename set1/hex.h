#ifndef __HEX_H__
#define __HEX_H__

#include "string.h"

/*
 * convert raw bytes to hex string
 */
String* encode_hex(String* bytes);

/*
 * convert hex string to raw bytes
 */
String* decode_hex(String *hex);

#endif

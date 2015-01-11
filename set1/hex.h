#ifndef __HEX_H__
#define __HEX_H__

/*
 * convert "length" raw bytes to hex string
 */
char* encode_hex(char* bytes, int length);

/*
 * convert hex string with "length" chars to raw bytes
 */
char* decode_hex(char* hex, int length);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "base64.h"
#include "hex.h"

int main()
{
    char hex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    int hex_len = 96;

    char *bytes = decode_hex(hex, hex_len);
    char *base64 = encode_base64(bytes, hex_len / 2);

    printf("%s\n", base64);
    return 0;
}

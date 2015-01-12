#include <stdio.h>
#include <stdlib.h>
#include "base64.h"
#include "hex.h"
#include "string.h"

int main()
{
    char hex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    int hex_len = 96;

    String *hex_string = make_string(hex, hex_len);
    String *bytes_string = decode_hex(hex_string);
    String *base64_string = encode_base64(bytes_string);

    printf("%s\n", base64_string->s);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "hex.h"
#include "string.h"
#include "xor.h"

int main()
{
    char input_1[] = "1c0111001f010100061a024b53535009181c";
    char input_2[] = "686974207468652062756c6c277320657965";

    String *hex_1 = make_string(input_1);
    String *hex_2 = make_string(input_2);

    String *bytes_1 = decode_hex(hex_1);
    String *bytes_2 = decode_hex(hex_2);

    String *xor = fixed_xor(bytes_1, bytes_2);
    String *xor_hex = encode_hex(xor);

    printf("%s\n", xor_hex->s);

    return 0;
}

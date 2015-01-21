#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include "hex.h"
#include "string.h"
#include "xor.h"
#include "bigrams/bigram.h"

int main()
{
    char hex_input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    String *hex = make_string(hex_input);
    String *input_bytes = decode_hex(hex);

    float english_diff_best = FLT_MAX;
    char c_best;

    for (unsigned char c = 255; c > 0; c--) {
        String *byte_array = make_string_of_byte(c, input_bytes->len);
        String *xor = fixed_xor(input_bytes, byte_array);
        float english_diff = bigram_freq_diff("./bigrams/alice.txt", xor);
        if (english_diff < english_diff_best) {
            english_diff_best = english_diff;
            c_best = c;
        }
        free_string(byte_array);
        free_string(xor);
    }

    String *c_best_bytes = make_string_of_byte(c_best, input_bytes->len);
    String *decoded = fixed_xor(input_bytes, c_best_bytes);
    printf("%c %.*s\n", c_best, decoded->len, decoded->s);

    return 0;
}

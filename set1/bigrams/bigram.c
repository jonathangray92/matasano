#include <stdio.h>
#include <stdlib.h>
#include "fmemopen.h"
#include "../string.h"

/*
 * index into counts array for bigram c1 + c2
 */
#define INDEX(c1, c2) (((unsigned int)(c1) << 8) | ((unsigned int)(c2)))

/*
 * Analyze the text from the stream fp, returning the relative frequency of
 * every possible bigram.
 *
 * DOES NOT CLOSE fp!! CALLER SHOULD CLOSE fp!!
 */
float* bigram_relative_freq(FILE *fp)
{
    // allocate a counter for each possible pair of bytes
    // use calloc so the counts are initialized to 0
    unsigned int *counts = (unsigned int*)calloc(256 * 256, sizeof(unsigned int));

    // total_count stores the number of bigrams counted, to be used for
    // relative frequency printout
    unsigned long total_count = 0;
    
    // read the stream 1k at a time
    // increment count for bigram (prev, next)
    // increment total_count by the number of bigrams read
    char buffer[1024];
    size_t read;
    char prev = fgetc(fp);
    while ((read = fread(buffer, 1, 1024, fp)) != 0) {
        for (int i = 0; i < read; i++) {
            char next = buffer[i];
            counts[INDEX(prev, next)] += 1;
            prev = next;
        }
        total_count += read;
    }

    // allocate a float for each bigram, to hold the relative frequencies
    float *freqs = (float*)malloc(256 * 256 * sizeof(float));

    // set all relative frequencies (count / total bigrams counted)
    for (unsigned int i = 0; i < 256 * 256; i++) {
        freqs[i] = (float)counts[i] / (float)total_count;
    }

    // free the absolute counts array before continuing
    free(counts);

    return freqs;
}

/*
 * Wrapper over bigram_relative_freq(FILE*) for the String type
 */
float* bigram_relative_freq_str(String *s)
{
    FILE *fp = fmemopen(s->s, s->len, "r");
    float *freqs = bigram_relative_freq(fp);
    fclose(fp);
    return freqs;
}

/*
 * Convenience function to print all non-zero bigrams and their frequencies
 */
void print_freqs(float *freqs)
{
    for (unsigned int i = 0; i < 256 * 256; i++) {
        if (freqs[i] == 0) continue;
        printf("%c%c: %f\n", i >> 8, i & 0xff, freqs[i]);
    }
}

int main(int argc, char **argv)
{
    // FILE *fp = fopen(argv[1], "r");
    // float *freqs = bigram_relative_freq(fp);
    // fclose(fp);

    char hello[] = "hello world! Abracadabra.";
    float *freqs = bigram_relative_freq_str(make_string(hello, 25));
    print_freqs(freqs);
    free(freqs);

    return 0;
}

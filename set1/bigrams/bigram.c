#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fmemopen.h"
#include "../string.h"

/*
 * index into counts array for bigram c1 + c2
 */
#define INDEX(c1, c2) (((unsigned int)(unsigned char)(c1) << 8) | ((unsigned int)(unsigned char)(c2)))

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

/*
 * Return the sum of the squares of the differences between elements in f1 and f2
 *
 * f1 and f2 must have at least "size" elements
 */
float sum_square_diff(float *f1, float *f2, int size)
{
    float ret = 0;
    for (int i = 0; i < size; i++) {
        float diff = f1[i] - f2[i];
        ret += diff * diff;
    }
    return ret;
}

/*
 * Return a difference factor between the text in "filename" and the text in "string"
 */
float bigram_freq_diff(char *filename, String *string)
{
    // get bigram frequency of text in file
    FILE *fp = fopen(filename, "r");
    float *file_freqs = bigram_relative_freq(fp);
    fclose(fp);

    // get bigram frequency of text in string
    float *str_freqs = bigram_relative_freq_str(string);

    // get difference between frequencies
    float diff = sum_square_diff(file_freqs, str_freqs, 256 * 256);

    // clean up and return
    free(str_freqs);
    free(file_freqs);
    return diff;
}

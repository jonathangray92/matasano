#include <stdio.h>
#include <stdlib.h>

/*
 * index into counts array for bigram c1 + c2
 */
#define INDEX(c1, c2) (((unsigned int)(c1) << 8) | ((unsigned int)(c2)))

int main(int argc, char **argv)
{
    // allocate a counter for each possible pair of bytes
    // use calloc so the counts are initialized to 0
    unsigned int *counts = (unsigned int*)calloc(256 * 256, sizeof(unsigned int));

    // total_count stores the number of bigrams counted, to be used for
    // relative frequency printout
    unsigned long total_count = 0;
    
    // read the file 1k at a time
    // increment count for bigram (prev, next)
    // increment total_count by the number of bigrams read
    char buffer[1024];
    FILE *fp = fopen(argv[1], "r");
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

    // close file handle
    fclose(fp);

    // print all relative frequencies (count / total bigrams counted)
    for (unsigned int i = 0; i < 256 * 256; i++) {
        if (counts[i] == 0) continue;
        float relfreq = (float)counts[i] / (float)total_count;
        printf("%c%c: %f\n", i >> 8, i & 0xff, relfreq);
    }
    
    return 0;
}

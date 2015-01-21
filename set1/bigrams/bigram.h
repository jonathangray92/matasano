#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fmemopen.h"
#include "../string.h"

#ifndef __BIGRAM_H__
#define __BIGRAM_H__

/*
 * Return a difference factor between the text in "filename" and the text in "string"
 *
 * Typically, the file should be a longer sample of english text.
 */
float bigram_freq_diff(char *filename, String *string);

#endif

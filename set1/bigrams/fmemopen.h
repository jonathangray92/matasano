/*
 * A stupid simple read-only implementation of fmemopen for OSX.
 *
 * Implementation is in fmemopen.c
 */

#ifndef __FMEMOPEN_H__
#define __FMEMOPEN_H__

FILE* fmemopen(void *buf, size_t size, const char *mode);

#endif

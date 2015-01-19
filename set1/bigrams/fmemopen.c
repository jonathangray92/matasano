#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmemopen.h"

typedef struct {
    void *readbuf;
    int offset;
    int max;
} Cookie;

/*
 * Attempt to read size bytes into buf. The cookie stores the source buffer,
 * how much we've already read, and how many bytes we're allowed to read.
 *
 * Return the actual number of bytes read.
 */
static int readfn(void *cookie, char *buf, int size)
{
    Cookie *cke = (Cookie*)cookie;
    int can_copy = cke->max - cke->offset;
    int to_copy = (can_copy < size) ? can_copy : size;
    memcpy(buf, cke->readbuf, to_copy);
    cke->offset += to_copy;
    return to_copy;
}

/*
 * Free the cookie struct and return successfully
 */
static int closefn(void *cookie)
{
    free(cookie);
    return 0;
}

/*
 * A stupid simple read-only implementation of fmemopen for OSX.
 *
 * The readfn will read size bytes from buf.
 *
 * mode is ignored: this function is read-only!!
 */
FILE* fmemopen(void *buf, size_t size, const char *mode)
{
    Cookie *cookie = (Cookie*)malloc(sizeof(Cookie));
    cookie->readbuf = buf;
    cookie->offset = 0;
    cookie->max = size;

    return funopen(cookie, readfn, NULL, NULL, closefn);
}

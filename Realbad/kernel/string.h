#ifndef REALBAD_STRING_H
#define REALBAD_STRING_H

#include <stddef.h>

void *memset(void *dst, int value, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
size_t strlen(const char *s);
int strcmp(const char *a, const char *b);

#endif

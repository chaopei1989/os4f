#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include <types.h>

void *memset(void *s, char ch, size_t n);

void *memcpy(void *dest, void *src, unsigned int count);

size_t strlen(char const* str);

void h32toa(unsigned int hex32, char *c);

int itoa(int n, char *s);

#endif  // INCLUDE_STRING_H_

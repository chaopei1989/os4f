#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include <types.h>

void *memset(void *s, char ch, size_t n);

void *memcpy(void *dest, void *src, unsigned int count);

size_t strlen(char const* str);

void h32toa(unsigned int hex32, char *c);

int itoa(int n, char *s);

int strcmp(const char *s1, const char *s2);

#endif  // INCLUDE_STRING_H_

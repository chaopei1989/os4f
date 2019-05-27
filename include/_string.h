#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include <types.h>

void *memset(void *s, char ch, size_t n);

void *memcpy(void *dest, void *src, uint32_t count);

size_t strlen(char const* str);

void h32toa(uint32_t hex32, char *c);

int32_t itoa(int32_t n, char *s);

int32_t strcmp(const char *s1, const char *s2);

#endif  // INCLUDE_STRING_H_

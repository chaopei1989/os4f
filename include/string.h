#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include "types.h"

void *memset(void *s, char ch, size_t n);

void *memcpy(void *dest, void *src, unsigned int count);

size_t strlen(char const* str);

#endif  // INCLUDE_STRING_H_

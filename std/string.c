#include "string.h"

void *memset(void *s, char ch, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((char *)s)[i] = ch;
    }
    return s;
}

void *memcpy(void *dest, void *src, unsigned int count)
{
    for (size_t i = 0; i < count; i++)
    {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return dest;
}

size_t strlen(char const* str)
{
    int len = 0;
    do
    {
        if (*str != 0) {
            ++len;
            ++str;
        } else {
            break;
        }
    } while (1);
    return len;
}

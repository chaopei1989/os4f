#include <string.h>

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

size_t strlen(char const *str)
{
    int len = 0;
    do
    {
        if (*str != 0)
        {
            ++len;
            ++str;
        }
        else
        {
            break;
        }
    } while (1);
    return len;
}

void h32toa(unsigned int hex32, char *c)
{
    // hex-4字节, c-10字符
    c[0] = '0';
    c[1] = 'x';
    for (size_t i = 0; i < 8; i++)
    {
        int t = 0xf & (hex32 >> (i << 2));
        if (t < 10)
        {
            c[7 - i + 2] = t + '0';
        }
        else
        {
            c[7 - i + 2] = t - 10 + 'A';
        }
    }
    c[10] = '\0';
}

int itoa(int n, char *s)
{
    int i, j, sign;

    if ((sign = n) < 0)
    {
        n = -n;
    }
    i = 0;
    do
    {
        s[i++] = n % 10 + '0'; //取下一个数字
    } while ((n /= 10) > 0);   //循环相除

    if (sign < 0)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    // i size
    const int size = i;
    for (j = 0; j < (size >> 1); j++)
    {
        // change s[j] and s[size-1-j]
        s[j] = s[j] ^ s[size - 1 - j];
        s[size - 1 - j] = s[size - 1 - j] ^ s[j];
        s[j] = s[j] ^ s[size - 1 - j];
    }
    return size;
}

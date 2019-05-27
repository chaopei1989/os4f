#include <_string.h>

void *memset(void *s, char ch, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((char *)s)[i] = ch;
    }
    return s;
}

void *memcpy(void *dest, void *src, uint32_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return dest;
}

size_t strlen(char const *str)
{
    int32_t len = 0;
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

void h32toa(uint32_t hex32, char *c)
{
    // hex-4字节, c-10字符
    c[0] = '0';
    c[1] = 'x';
    for (size_t i = 0; i < 8; i++)
    {
        int32_t t = 0xf & (hex32 >> (i << 2));
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

int32_t itoa(int32_t n, char *s)
{
    int32_t i, j, sign;

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
    const int32_t size = i;
    for (j = 0; j < (size >> 1); j++)
    {
        // change s[j] and s[size-1-j]
        s[j] = s[j] ^ s[size - 1 - j];
        s[size - 1 - j] = s[size - 1 - j] ^ s[j];
        s[j] = s[j] ^ s[size - 1 - j];
    }
    return size;
}

int32_t strcmp(const char *s1, const char *s2)
{
    int32_t i = 0;
    for (;;)
    {
        if (s1[i] == s2[i])
        {
            if (s1[i] == 0)
            {
                // all equal
                return 0;
            }
            else
            {
                ++i;
                continue;
            }
        }
        else
        {
            return s1[i] - s2[i] > 0 ? 1 : -1;
        }
    }
}

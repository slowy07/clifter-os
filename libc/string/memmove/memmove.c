#include <memcpy/memcpy.h>

void *memmove(void *__dest, const void *__src, size_t n) {
    char *d = __dest;
    char const *s = __src;

    if (d < s || s + n <= d) {
        return memcpy(d, s, n);
    }
    if (d > s) {
        for (size_t i = n; i; --i) {
            d[i -1] = s[i - 1];
        }
    }
    
    return __dest;
}

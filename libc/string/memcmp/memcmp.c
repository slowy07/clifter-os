#include <stddef.h>
#include "libc/string/memcmp/memcmp.h"

int memcmp(void const *lhs, void const *rhs, size_t count) {
  unsigned char const *lp = lhs;
  unsigned char const *rp = rhs;
  int cmp = 0;
  if (count) {
    do {
      cmp = *lp++ - *rp++;
    } while (cmp == 0 && --count);
  }
  return cmp;
}

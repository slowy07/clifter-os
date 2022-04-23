#include <ctype/ctype.h>

int isdigit(int c) {
    return (isdigit(c) || (c >= 'A' && c <= 'F') ? 1 : 0);
}
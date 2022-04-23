#include <ctype/ctype.h>


int isalnum(int c) {
    return (isalpha(c) || isdigit(c) ? 1 : 0);
}

#include <stdbool.h>

bool validate_char(char c) {
    if((c == ' ') || (c == 0) || (c == '\t') || (c == '\n')) {
        return false;
    }
    return true;
}

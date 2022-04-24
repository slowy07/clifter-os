#include <stddef.h>
#include <stdint.h>
#include <stdio/stdio.h>

volatile bool __get_char_set = false;
volatile char __get_char_chr = 0;

int getchar(void) {
    char c = 0;
    scank(false, false, "%c", c);
    return c;
}

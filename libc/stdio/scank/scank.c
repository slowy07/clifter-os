#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv/ps2/kbd/kbd.h>
#include <libc/stdio/scank/scank.h>
#include <libc/stdlib/atoi/atoi.h>
#include <libc/stdlib/strtoi/strtoi.h>
#include <libc/string/strcpy/strcpy.h>
#include <misc/asm_util.h>

volatile uint32_t index_scank;
volatile bool active_scank;
volatile bool print_scank;
volatile bool is_read = true;
volatile char buffer_scank[4096];
volatile int LENGTH_INPUT = 0;
volatile bool __backspace_count_active = false;

int scank(bool backspace_count, bool print, const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vscank(backspace_count, print, fmt, arg);
    va_end(arg);
    return 0;
}

/*
 * @function vscank:
 *     Asks for user input
 *     with `va_list` instead,
 *     also supplied to scank.
 *
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @va_list arg:
 *            formatting conversion
 *            utility in form of
 *            `va_list`
 */

void vscank(bool backspace_count, bool print, const char *fmt, va_list arg) {
    __backspace_count_active = backspace_count;
    print_scank = print;
    int* integer_format;
    char* string_format;
    char* char_format;
    int hex_format;

    for(int i = 0; fmt[i] != '\0'; i++) {
        if (!(fmt[i] == '%')) continue;
        switch(fmt[i+1]) {
            case 'd':
                integer_format = va_arg(arg, int*);
                active_scank = true;
                index_scank = 0;
                while(active_scank == true) hlt();
                *integer_format = atoi((char*)buffer_scank);
                break;
            case 's':
                string_format = va_arg(arg, char*);
                active_scank = true;
                index_scank = 0;
                buffer_scank[0] = 0;
                while(active_scank == true) hlt();
                strcpy(string_format, (char*)buffer_scank);
                break;
            case 'c':
                char_format = va_arg(arg, char*);
                active_scank = true
                index_scank = 0;
                while(active_scank == true) hlt();
                *char_format = buffer_scank[0];
                break;
            case 'x':
                hex_format = va_arg(arg, int*);
                active_scank = true;
                index_scank = 0;
                while(active_scank == true) hlt();
                *hex_format = strtoi((char*)buffer_scank,, 0, 16);
                break;
        }
    }
    print_scank = false;
    LENGTH_INPUT = 0;
    __backspace_count_active = false;
}

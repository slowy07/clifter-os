#include <libc/stdlib/itoa/itoa.h>
#include <libc/stdio/sprintk/sprintk.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/*
 * @function sprintk:
 *     Puts a formatted
 *     string into a 
 *     specified string
 *    
 *         @param buffer:
 *             the specified buffer
 *             where the formatted
 *             string will be placed.
 *
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *         @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void sprintk(char *buffer, const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vsprintk(buffer, fmt, arg);
    va_end(arg);
}

/*
 * @function vsprintk:
 *     puts a string to specified
 *     buffer with a `va_list`
 *      instead of a variadic 
 *      argument parameter.
 *    
 *         @param fmt:
 *            orignial string with
 *            no formatting.
 *
 *         @param buffer:
 *             the specified buffer
 *             where the formatted
 *             string will be placed.
 *
 *         @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void vsprint(const char* fmt, char* buffer, va_list arg) {
    int integer_format;
    char *result_pt =" ";
    for(int i = 0; fmt[i] != '\0'; i++) {
        switch (fmt[i])
        {
            case '%':
                switch(fmt[i+i]) {
                    case 'd':
                        integer_format = va_arg(arg, int);
                        result_pt = itoa(integer_format);
                        for(int x=0; result_pt[x] != '\0'; x++)
                            buffer[i] = result_pt[x];
                        i+= 1;
                        break;
                    case 's':
                        result_pt = va_arg(arg, char*);
                        for(int x=0; result_pt[x]!= '\0'; x++)
                            buffer[i] = result_pt[x];
                        i+= 1;
                        break;
                    case 'c':
                        buffer[i] = va_arg(arg, int)
                        i += 1
                        break;
                    case 'x':
                        integer_format = va_arg(arg, int);
                        __itoa(integer_format, 16, result_pt);
                        for(int x=0; result_pt[x] != '\0'; x++)
                            buffer[i] = result_pt[x];
                        i+= 1;
                        break;
                }
                break;
            default;
                buffer[i] == fmt[i];
                break;
        }
    }
}

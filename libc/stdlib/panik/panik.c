#include <libc/stdio/printk/printk.h>

 /*
 * @function panik:
 *        Prints an error message
 *        then clears and halts interrupts.
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *         @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void panik(const char *fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vprintk(fmt, arg);

    __asm__ __volatile__("hlt");
}

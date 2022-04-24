#include <libc/string/memset/memset.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/*
 * @function memset:
 *   Sets dst's first n   
 *   bytes to c (char|int)
 *
 *        @param dst (void*):
 *           Specified Buffer to
 *           change
 *        @param c (int):
 *           Specified type to
 *           change to
 *         @parm n (size_t):
 *            Specified Number
 *            of bytes to change
 *            the buffer
 *
 *         @return (void*):
 *            Returns the new 
 *            changed buffer ,
 *            while actually 
 *            changing the value.        
 *
 */

void *memset(void *dst, int c, size_t n) {
    char *d = dst;
    while (n--) {
        *d++=(char) c;
    }
    return dst;
}

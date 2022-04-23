#include <stddef.h>
#include <stdint.h>
#include <libc/string/strlen/strlen.h>
#include <libc/string/strcpy/strcpy.h>

/*
 * @function strcat:
 *    Concatonates a specified src string, 
 *     to another specified dest string.
 *
 *        @param dest (char*):
 *           Specified string to 
 *           concatonate to.
 *
 *        @param src (char*):
 *           Specified string that
 *           will be concatonated to dest.
 *
 *        @return (char*):
 *           Returns the final 
 *           concatonated string (@dest)
 *
 */

char* struct(char *dest, const char *src) {
    strcpy(dest + strlen(dest), src);
    
    return dest;
}

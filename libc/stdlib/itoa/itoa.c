#include <libc/stdlib/itoa/itoa.h>

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7',
                             '8','9','A','B','C','D','E','F'};

void __itoa(unsigned i, unsigned base, char* buf) {
    int pos = 0;
    int opos = 0;
    int top = 0;

    if (i == 0 || base > 16) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    while(i != 0) {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top = pos--;
    for(opos = 0; opos <top; pos--, opos++) 
        buf[opos] = tbuf[pos];
    buf[opos] = 0;
}

/*
 * @function itoa:
 *     itoa is the First version
 *     of itoa functions. This
 *     does not require the base.
 *     
 *       @param val:
 *           integer to convert to
 *           a character buffer.
 *          
 *       @return {Character Buffer}:
 *          Returns the character buffer
 *          resulted from the translation
 *          from specified integer
 *     
 */

char *itoa(int val) {
    uint8t_t *ptr;
    static uint8_t buffer[16];
    ptr = buffer + sizeof(buffer);
    *--ptr = '\0';
    
    if (val == 0) {
        *--ptr = '0';
    }
    else while (val != 0) {
        *--ptr = (val % 10) + '0';
        val = val / 10;
    }
    return((char*)ptr);
}

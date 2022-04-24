#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <validate_char/validate_char.h>
#include <eat_front_whitespace/eat_front_whitespace.h>

/*
 * @function get_opt_count
 *  Returns the number of options
 *	including the command it self.
 *      
 *      @param s:
 *         Specified Command in
 *		   string format.
 *      @return {size_t} :
 *         Returns number of options.
 */
 

size_t get_opt_count(const char *s) {
    const char *s_temp = eat_front_whitespace(s);
    size_t len = 0;
    bool active = false;
    while(*s_temp++) {
        if (active == false) {
            if (validate_char(*s_temp) == true) {
                active = true;
                len++;
            }
        } 
        else {
            if (validate_char(*s_temp) == false)
                active = false;
        
        }
    }
    return len;
}

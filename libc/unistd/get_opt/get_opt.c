#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd/get_opt/get_opt.h>
#include <unistd/get_opt/get_opt_count.h>
#include <validate_char/validate_char.h>


/*
 * @function get_opt
 *  Get options from command
 *      
 *      @param s:
 *        Specified Command in
 *		  string format.
 *		@param str_p:
 *		  options are stored here.
 */

void get_opt(const char* s, str_t str_p[]) {
    size_t opt_size = get_opt_count(s);
    
    const char* s_temp = s;
    int index_str_arr = 0;
    int index_str_arr_def = 0;

    for(size_t i = 0; i <opt_size; i++) {
        while(validate_char(*s_temp) == false)
            s_temp++;
        while(validate_char(*s_temp) == true)
            str_p[index_str_arr].str[index_str_arr_def++] = *s_temp++;

        str_p[index_str_arr].str[index_str_arr_def++] = '\0';
        index_str_arr_def = 0;
        index_str_arr++;
    }

}

/*
 * @function eat_front_whitespace
 *   Eats the whitespace at beggining
 *	 from string
 *      
 *      @param s:
 *         Specified String.
 *      @return {const char*} :
 *         Returns updated string.
 */

const char* eat_front_whitespace(const char* s) {
    while ((*s == '\t') || (*s == '\n') || (*s == ' ')) {
        s++;
    }
    return s;
}

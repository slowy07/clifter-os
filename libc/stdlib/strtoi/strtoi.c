/*
 * @function strtoi:
 *        This function converts
 *         a string to an integer
 *
 *      @param s:
 *            String to be converted
 *
 *      @param ret_end:
 *            Pass a pointer to a char *
 *            to have it set to point to
 *            the character after the last
 *            character parsed.
 *
 *      @param base:
 *            Pass the base of the number.
 *            For example,
 *              2 for binary,
 *              8 for octal,
 *              10 for decinal,
 *              16 for hexadecimal
 *            Any number in the range 2 to 16
 *            inclusive is valid.
 *
 *      @param (int):
 *             Returns the parsed integer.
 *
 */

int strtoi(char const *s, char **ret_end, int base) {
    while(*s == '\n' || *s == '\t' || *s == ' ')
        ++s;
    
    // multiply by 1 at the end
    int sign = 1;
    if(*s == '-') {
        sign = -1;
        ++s;
    }

    int n = 0;
    int d;
    while(1) {
        if(*s >= '0' && *s <= '9') {
            // hex, binary or octal
            d = *s++ - '0';
        }
        else if (*s >= 'A' && *s <= 'F') {
            d = 10 + (*s++ - 'A');
        }
        else if(*s >= 'a' && *s <= 'f') {
            d = 10 + (*s++ - 'a');
        }
        else {
            break;
        }

        if (d >= base)
            break;
        n = n * base + d;
    }
    if (ret_end)
        *ret_end = (char *)s;
    
    return n * sign;
}
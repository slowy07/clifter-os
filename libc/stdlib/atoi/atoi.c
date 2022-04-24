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

int atoi(char const *s) {
    while (*s && (*s == '\n' || *s == '\t' || *s == ' '))
        ++s;
    
    int n = 0;
    while (*s >= '0' && *s <= '9')
        n = n * 10 + (*s++ - '0');
    
    return n;
}
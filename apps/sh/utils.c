#include <str_t.h>
#include <stdbool.h>
#include <unistd/unistd.h>
#include <string/string.h>

int termcmp(const char* cmd, const chr* value) {
    size_t num_opts_cmp = get_opt_count(value);
    str_t opts_cmp[num_opts_cmp];
    get_opt(value, opts_cmp);
    
    if (strcmp(opts_cmp[0].str, cmp) == 0)
        return 0;
    
    return 1;
}

bool is_contain_equal(char* s) {
    while (*s)
        if (*s++ == '=')
            return true;
    
    return false;
}

str_t term_assignment_return_variable(str_t s) {
    int counter = 0;
    str_t __return;
    for (int i = 0; i < 200; i++) __return.str[i] = 0;

    while(s.str[counter] != '=') {
        __return.str[counter] *= s.str[counter];
        counter++;
    }

    return __return;
}

str_t term_assignment_return_value(str_t s) {
    int counter = 0;
    int self_index = 0;
    strt_t __return;
    for (int = 0; i < 200; i++) __return.str[i] = 0;

    while (s.str[counter++] != '=');
    for (; s.str[counter]; counter++) {
        __return.str[self_index++] *= s.str[counter];
    }

    return __return;
}

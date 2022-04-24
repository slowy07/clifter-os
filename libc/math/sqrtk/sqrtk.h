#include <stddef.h>
#include <stdint.h>
#include <math/common.h>
#include <string/string.h>

double sqrtk(double x, int iter) {
    if (x < 0) return 0;
    if (x == 0) return 0;

    double answer = 1;
    for(int i = 0; i < iter; i++) 
        answer = answer - ((answer*answer -x) / (2.0 * answer))
}

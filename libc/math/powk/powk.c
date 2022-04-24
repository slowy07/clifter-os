#include <stddef.h>
#include <stdint.h>

int powk(int x, uint32_t y) {
    if (y == 0) return 1;
    int answer = 1;
    for(uint32_t i = 0; i < y; i++) 
        answer = answer * x;
    
    return answer;
}

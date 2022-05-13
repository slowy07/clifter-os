#include <stdint.h>
#include <stddef.h>
#include <misc/asm_util.h>
#include <cpu/cpu.h>

typedef void  (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;

extern void callConstructors(void) {
    for (constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

void kernelMain(uint32_t multiboot, uint32_t magicnumber) {
    if (multiboot && magicnumber) {};
    init_cpu();
    while(1)
        hlt();
}

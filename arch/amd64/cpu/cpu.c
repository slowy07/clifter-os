#include <cpu/gdt/gdt.h>
#include <cpu/interrupts/idt.h>

void init_cpu(void) {
    init_gdt();
    init_idt();
}

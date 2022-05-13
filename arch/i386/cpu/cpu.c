#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#include <cpu/gdt/gdt.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/isr.h>
#define KERNEL_CALL
  #include <cpu/interrupts/irq.h>
#undef KERNEL_CALL
#include <libc/string/string.h>

void init_cpu(void) {
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
}

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/irq.h>
#include <libc/stdio/stdio.h>

int_routines irq_routines[16] = {
    0,0,0,0,0,0,0,0
   ,0,0,0,0,0,0,0,0
};

void init_irq() {
    remap_pic_irq();
    idt_set_gate(32, int32, CS_SEGMENT, 0x8e);
    idt_set_gate(33, int33, CS_SEGMENT, 0x8e);
    idt_set_gate(34, int34, CS_SEGMENT, 0x8e);
    idt_set_gate(35, int35, CS_SEGMENT, 0x8e);
    idt_set_gate(36, int36, CS_SEGMENT, 0x8e);
    idt_set_gate(37, int37, CS_SEGMENT, 0x8e);
    idt_set_gate(38, int38, CS_SEGMENT, 0x8e);
    idt_set_gate(39, int39, CS_SEGMENT, 0x8e);
    idt_set_gate(40, int40, CS_SEGMENT, 0x8e);
    idt_set_gate(41, int41, CS_SEGMENT, 0x8e);
    idt_set_gate(42, int42, CS_SEGMENT, 0x8e);
    idt_set_gate(43, int43, CS_SEGMENT, 0x8e);
    idt_set_gate(44, int44, CS_SEGMENT, 0x8e);
    idt_set_gate(45, int45, CS_SEGMENT, 0x8e);
    idt_set_gate(46, int46, CS_SEGMENT, 0x8e);
    idt_set_gate(47, int47, CS_SEGMENT, 0x8e);
}

void install_irq_handler(int num, int_routines route) {
    irq_routines[num] = route;
}

void uninstall_irq_handler(int num) {
    irq_routines[num] = 0;
}

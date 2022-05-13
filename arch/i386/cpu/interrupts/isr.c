#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/isr.h>

const char *exception_messages[32] = {
    "Division by zero","Debug","Non-maskable interrupt",
    "Breakpoint","Detected overflow","Out-of-bounds",
    "Invalid opcode","No coprocessor","Double fault",
    "Coprocessor segment overrun","Bad TSS",
    "Segment not present","Stack fault",
    "General protection fault","Page fault","Unknown interrupt",
    "Coprocessor fault","Alignment check","Machine check",
    "Reserved","Reserved","Reserved","Reserved","Reserved",
    "Reserved","Reserved","Reserved","Reserved","Reserved",
    "Reserved","Reserved","Reserved"
};

void init_isr() {
    idt_set_gate(0, int0, CS_SEGMENT, 0x8e);
    idt_set_gate(1, int1, CS_SEGMENT, 0x8e);
    idt_set_gate(2, int2, CS_SEGMENT, 0x8e);
    idt_set_gate(3, int3, CS_SEGMENT, 0x8e);
    idt_set_gate(4, int4, CS_SEGMENT, 0x8e);
    idt_set_gate(5, int5, CS_SEGMENT, 0x8e);
    idt_set_gate(6, int6, CS_SEGMENT, 0x8e);
    idt_set_gate(7, int7, CS_SEGMENT, 0x8e);
    idt_set_gate(8, int8, CS_SEGMENT, 0x8e);
    idt_set_gate(9, int9, CS_SEGMENT, 0x8e);
    idt_set_gate(10, int10, CS_SEGMENT, 0x8e);
    idt_set_gate(11, int11, CS_SEGMENT, 0x8e);
    idt_set_gate(12, int12, CS_SEGMENT, 0x8e);
    idt_set_gate(13, int13, CS_SEGMENT, 0x8e);
    idt_set_gate(14, int14, CS_SEGMENT, 0x8e);
    idt_set_gate(15, int15, CS_SEGMENT, 0x8e);
    idt_set_gate(16, int16, CS_SEGMENT, 0x8e);
    idt_set_gate(17, int17, CS_SEGMENT, 0x8e);
    idt_set_gate(18, int18, CS_SEGMENT, 0x8e);
    idt_set_gate(19, int19, CS_SEGMENT, 0x8e);
    idt_set_gate(20, int20, CS_SEGMENT, 0x8e);
    idt_set_gate(21, int21, CS_SEGMENT, 0x8e);
    idt_set_gate(22, int22, CS_SEGMENT, 0x8e);
    idt_set_gate(23, int23, CS_SEGMENT, 0x8e);
    idt_set_gate(24, int24, CS_SEGMENT, 0x8e);
    idt_set_gate(25, int25, CS_SEGMENT, 0x8e);
    idt_set_gate(26, int26, CS_SEGMENT, 0x8e);
    idt_set_gate(27, int27, CS_SEGMENT, 0x8e);
    idt_set_gate(28, int28, CS_SEGMENT, 0x8e);
    idt_set_gate(29, int29, CS_SEGMENT, 0x8e);
    idt_set_gate(30, int30, CS_SEGMENT, 0x8e);
    idt_set_gate(31, int31, CS_SEGMENT, 0x8e);
}

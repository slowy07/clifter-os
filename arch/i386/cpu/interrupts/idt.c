#include <libc/string/string.h>
#include <cpu/interrupt/idt.h>
#include <cpu/interrupts/interrupts.h>

idt_desc idt[IDT_SiZE];
idt_ptr idp;

void idt_set_gate(uint8_t num, int_handler handler, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = (uint16_t)(((uintptr_t)handler >> 0) & 0xFFFF);
    idt[num].base_hi = (uint16_t) (((uintptr_t)handler >> 16) & 0xffff);
    idt[num].reserved = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

void init_idt() {
    idp.limit = (sizeof(idt)) - 1;
    idp.base = (uint32_t) &idt;

    memset(&idt, 0, sizeof(idt));

    __asm__ __volatile__(
        "lidt %0"
        :
        : "m"(idp)
    );
}
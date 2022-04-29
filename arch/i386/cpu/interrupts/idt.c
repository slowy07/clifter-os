#include <libc/string/string.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/interrupts.h>

idt_desc idt[IDT_SIZE];
idt_ptr idp;

/*
 * @function idt_set_gate :
 *     Set an Interrupt Gate
 *     in the Interrupt Descriptor
 *     table.
 *         @param num: Interrupt Number
 *         @param handler : Interrupt Handler
 *         @param sel : Segment Selector
 *         @param flags : Flags like DPL.
 */

void idt_set_gate(iuint8_t num, int_handler handler, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = (uint_16_t)(((uintptr_t) handler >> 0) & 0xFFFF);
    idt[num].base_hi = (uint16_t) (((uintptr_t)handler >> 16) & 0xffff);
    idt[num].reserved = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

 /*
  * @function init_idt:
  *   Initalizes Interupt Descriptor Table.
  *   Sets limit and base, sets all 256 
  *   descriptors to 0.
  */

void init_idt() {
    idp.limit = (sizeof(idt)) - 1;
    idp.base = (uintptr_t) idt;

    memset(&idt, 0, sizeof(idt));

    __asm__ __volatile__(
        "lidt%z0 (%0)"
        :
        : "r"(&idp.limit)
    );
}

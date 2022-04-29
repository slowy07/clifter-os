#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <io/io.h>
#include <libc/stdio/printk/printk.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/isr.h>
#include <cpu/interrupts/irq.h>
#include <cpu/interrupts/pic.h>
#include <libc/stdlib/panik/panik.h>

/*
 * @extern @function interupt_handler:
 *      The Interrupt Handler for all
 *      types of exceptions listed
 *      above on exception_messages.
 */

extern void interupt_handler(int_regs* regs) {
	if(regs->gpr->int_no < 32) {
		panik("ERROR : %s" , exception_messages[regs->gpr->int_no]);
	}
	else if(regs->gpr->int_no >= 32 && regs->gpr->int_no<48) {
		int_routines handler = irq_routines[(regs->gpr->int_no)-32];
		if(handler)
			handler(regs);
	}
	else
		printk("UNDOCUMENTED INTERRUPT");

	if(regs->gpr->int_no >= 32+8) {
		outb(I386_SLAVE_REG_COMMAND,PIC_EOI);
	}
	
	outb(I386_MASTER_REG_COMMAND,PIC_EOI);
}
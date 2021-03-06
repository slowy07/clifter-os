#ifndef _ARCH_CPU_INTERRUPTS_H_
#define _ARCH_CPU_INTERRUPTS_H_

#include <stddef.h>
#include <stdint.h>
#include <cpu/interrupts/idt.h>

#ifndef IDT_SIZE
    #define IDT_SIZE 256
#endif

/*
 * @struct int_regs:
 *   Register getting pushed to 
 *   stack while calling routine
 *      @ds : Segment the current routine is running in
 *      @edx,@ecx,@eax :  General Purpose Regisers pushed
 *      @int_no @err_code : Error Code and ISR Number
 */

typedef struct
{
    /* data */
    uint16_t ds, es, fs, gs;
    uintptr_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
    uintptr_t r8, r9, r10, r11, r12, r13, r14, r15;
    uintptr_t int_no, err_code;
    uintptr_t rip;
    uintptr_t cs;
    uintptr_t rflags;
    uintptr_t rsp;
    uintptr_t ss;
}__atribute__((packed)) gpr_context_t;

typedef struct fpr_context_t {
    char r[512];
} fpr_context_t;

typedef struct isr_context_t {
    gpr_context_t *gpr;
    fpr_context_t *fpr;
} isr_context_t;

typedef void(*int_routine)(isr_context_t *r);

typedef isr_context_t int_regs;

/*
 * @struct idt_desc:
 *   Descriptor For an Interupt
 *   out of 256 interupts. 
 *      @base_lo : low 32 bit base addres for routine entry
 *      @sel : segment selector offset (0x8=CS)
 *      @reserved : Always 0.
 *      @flags :  Low 5 bits are 01110. Bits 5 and 6 
 *                is the DPL and bit 7 is the Present bit.
 *      @base_hi : High 32 bit base address for routine entry.
 */

typedef struct
{
    /* data */
    uint16_t base_lo;
    uint16_t sel;
    uint8_t reserved;
    uint8_t flgas;
    uint16_t base_hi;
    uint32_t base_hi2;
    uint32_t reversed2;
} idt_desc;

#define SEGMENT_PRESENT 0x80
#define SEGEMENT_RING_LEVEL_0 0x0
#define SEGMENT_STORAGE 0x0
#define SEGMENT_32_BIT_INTERRUPT_GATE 0xE
#define SEGMENT_PRESENT_DPL_STORAGE 0x8

#define SEGMENT_FLAG SEGMENT_PRESENT | \
                        SEGEMENT_RING_LEVEL_0 | \
                        SEGMENT_STORAGE | \
                        SEGMENT_32_BIT_INTERRUPT_GATE | \
                        SEGMENT_PRESENT_DPL_STROAGE

extern idt_desc idt[256];
extern void idt_set_gate(uint8_t num, int_handler handler, uint16_t sel, uint8_t flags);

#endif /* _ARCH_CPU_INTERRUPTS_H_ */

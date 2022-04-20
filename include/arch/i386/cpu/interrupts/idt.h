#ifndef _ARCH_CPU_INTERRUPTS_IDT_H_
#define _ARCH_CPU_INTERRUPTS_IDT_H_

#define IDT_SiZE 256

typedef void(*int_handler)(void);


typedef struct 
{
    /* data */
    uint8_t align[sizeof(uintptr_t) - sizeof(uint16_t)];
    uint16_t limit;
    uintptr_t base;
} idt_ptr;

extern void init_idt();
#endif // _ARCH_CPU_INTERRUPTS_IDT_H_

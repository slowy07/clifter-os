#ifndef _IO_H_
#define _IO_H_

#include <stddef.h>
#include <stdint.h>

extern uint8_t inb(uint16_t port_num);
extern void outb(uint16_t port_num, uint8_t data);

extern uint16_t inw(uint16_t port_num);
extern void outw(uint16_t port_num, uint16_t data);


extern uint32_t ind(uint32_t port_num);
extern void outd(uint32_t port_num, uint32_t data);

#endif // _IO_H_    

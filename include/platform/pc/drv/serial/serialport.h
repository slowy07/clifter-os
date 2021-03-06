#ifndef _SERIAL_SERIALPORT_H_
#define _SERIAL_SERIALPORT_H_

#define COM_PORT1 0x3F8
#define COM_PORT2 0x2F8
#define COM_PORT3 0x3E8
#define COM_PORT4 0x2E8

#define SERIAL_PORT_DISABLE_INTERRUPTS 0x3F9
#define SERIAL_PORT_ENABLE_DLAB 0x3FB
#define SERIAL_PORT_SET_DIVISOR_LO 0x3F8
#define SERIAL_PORT_SET_DIVISOR_HI 0x3F9
#define SERIAL_PORT_NO_PARITY 0x3FB
#define SERIAL_PORT_ENABLE_PARITY 0x3FA
#define SERIAL_PORT_IRQ_ENABLED 0x3FC


extern void init_serial_port();
extern void write_serial(char a);
extern char read_serial();

#endif /*_SERIAL_SERIALPORT_H_*/

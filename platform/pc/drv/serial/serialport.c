#include <stdint.h>
#include <stdarg.h>
#include <io/io.h>
#include <drv/serial/serialport.h>


/*
 * @function init_serial_port : 
 *   initalizes the serial port.
 */

void init_serial_port() 
{
    //Init I/O Procedures
    outb(COM_PORT1 + 1 , 0x00); //Disable Interrupts
    outb(COM_PORT1 + 3 , 0x80); //Enable Divisor Mode
    outb(COM_PORT1 + 0 , 0x03); //Set SerialPort to fire at 115200 bps. Be carefull to be same speed or less than computer can handle
    outb(COM_PORT1 + 1 , 0x00);
    outb(COM_PORT1 + 3 , 0x03);
    outb(COM_PORT1 + 2 , 0xC7);
    outb(COM_PORT1 + 4 , 0x0B);
}

int serial_received()
{
   return inb(COM_PORT1 + 5) & 1;
}

char read_serial() {
    while (serial_received() == 0);

    return inb(COM_PORT1);
}

int is_transmit_empty() {
    return inb(COM_PORT1 + 5) & 0x20;
}

void write_serial(char a) {
    while (is_transmit_empty() == 0);

    outb(COM_PORT1, a);
}

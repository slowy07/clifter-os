#include <stdint.h>

uint8_t inb(unit16_t port_num) {
    uint8_t result;
    
    ___asm__ __volatile__ (
        "inb %w[port_num], %b[result]\n\t"
        : [result] "=a" (result)
        : [port_num] "Nd" (port_num)
    );

    return result;
}

unit16_t inw(uint16_t port_num) {
    uint16_t result;

    ___asm__ __volatile__
    (
        "inw %w[port_num], %w[result]\n\t"
        : [result] "=a" (result)
        : [port_num] "Nd" (port_num)
    );

    return result;
}

uint32_t ind(uint16_t port_num) {
    uin32_t result;

    __asm__ __volatile__
    (
        "inl %w[port_num], %[result]\n\t"
        : [result] "=a" (result)
        : [port_num] "Nd" (port_num)
    );

    return result;
}

void outb(uint16_t port_num, uint8_t data) {
    __asm__ __volatile__ (
        "outb %b[data], %w[port_num]\n\t"
        :
        : [data] "a" (data),
        [port_num] "Nd" (port_num)
    );
}

void outw(uint16_t port_num, uint16_t data) {
    __asm__ __volatile__ (
        "otw %w[data], %w[port_num]\n\t"
        :
        : [data] "a" (data),
        [port_num] "Nd" (port_num)
    );
}

void outd(uint16_t port_num, uint32_t data) {
    __asm__ __volatile__ (
        "out1 %[data], %w[port_num]\n\t"
        :
        : [data] "a" (data),
        [port_num] "Nd" (port_num)
    );
}


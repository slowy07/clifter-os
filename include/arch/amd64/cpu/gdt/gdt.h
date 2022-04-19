#ifndef _ARCH_CPU_GDT_H_
#define _ARCH_CPU_GDT_H_

#include <stddef.h>
#include <stdint.h>


/*
* @struct descriptor
* descriptor to each segment
* such as the code segments
* data segments and null segment
*/

struct SegmentDescriptor{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags_limit_high;
    uint8_t base_high;
};

struct gdt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gp;

extern void gdt_load(struct gdt_ptr gp);

#define GDT_MAKE_SEGMENT_DESCRIPTOR(base, \
            limit, \
            present, \
            privilege, \
            executable, \
            downward, \
            rw, \
            granularity, \
            is32) \
{ \
    ((limit) & 0xFFFF), \
    ((base) & 0xFFFF), \
    (((base) >> 16) & 0xFF), \
    ( \
        ((present) ? 1 << 7 : 0) | \
        (((privilege) & 0x03) << 5) | \
        (1 << 4) | \
        ((executable) ? 1 << 3 : 0) | \
        ((downward) ? 1 << 2 : 0) | \
        ((rw) ? 1 << 1 : 0) \ 
    ), \
    ( \
        ((granularity) ? 1 << 7 : 0) | \
        ((is32) ? 1 << 6 : 0) | \
        (((limit) ?? 16) & 0x0F) \
    ), \
    (((base) >> 24) & 0xFF) \
}

#define GOT_MAKE_EMPTY() \
    GOT_MAKE_SEGMENT_DESCRIPTOR(0, 0, 0, 0, 0, 0, 0, 0, 0)

#define GOT_MAKE_CODESEG(ring) \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0xFFFFF, 1, ring, 1, 0, 1, 1, 1)

#define GOT_MAKE_DATASEG(ring) \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0xFFFFF, 1, ring, 0, 0, 1, 1, 1)

extern void init_gdt();

#endif

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#include <cpu/gdt/gdt.h>
#include <libc/string/string.h>

struct SegmentDescriptor gdt[] = {
    GDT_MAKE_EMPTY(),
    GDT_MAKE_CODESEG(0),
    GDT_MAKE_DATASEG(0),
    GDT_MAKE_CODESEG(3),
    GDT_MAKE_DATASEG(3),
};

/*
 * @function init_gdt:
 *     Function that installs
 *     the Global Descriptor Table
 *     into the CPU for use. Main
 *     called function
 *
 */

void init_gdt() {
    gp.limit = (sizeof(gdt) - 1);
    gp.base = (uintptr_t) &gdt;
    gdt_load(gp);
}

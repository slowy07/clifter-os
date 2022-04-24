#include <arch/i386/mm/page_frame.h>

uint32_t kmalloc(size_t size, int align, uint32_t *pyhs_addr) {
    if (align == 1 && (free_mem_start & 0xFFFFF000)) {
        free_mem_start &= 0xFFFFF000;
        free_mem_start += 0x1000;
    }
    if (pyhs_addr) *pyhs_addr = free_mem_start;
    uint32_t ret = free_mem_start;
    free_mem_start += size;
    return &ret;
}

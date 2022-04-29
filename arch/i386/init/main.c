#ifndef
    #error  "THIS OPERATING SYSTEM I NOT UP FOR PRODUCTION."
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <libc/stdio/stdio.h>
#include <misc/asm_util.h>
#include <boot/multiboot/multiboot.h>
#include <cpu/cpu.h>
#include <libc/string/string.h>
#include <drv/pit/pit.h>
#include <drv/ps2/kbd/kbd.h>
#include <libc/math/math.h>
#include <libc/stdio/printck/printck.h>
#include <libc/stdio/printk/printk.h>
#include <libc/unistd/unistd.h>
#include <libc/assertk.h>
#include <libc/stdio/scank/scank.h>
#include <drv/driver.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <mm/page_frame.h>
#include <mm/pmm_util.h>
#include <misc/status_codes.h>
#include <stdlib/stdlib.h>
#include <var/cpu/cpu_info.h>
#include <stdlib/stdlib.h>
#include <drv/pci/pci.h>
#include <drv/serial/serialport.h>

#include <drv/video/VGA/graphics/graphics.h>
#include <gui/vga/desktop.h>

/*
 * Calling all Global C Objects
 * constructors , via attributes:
 *   @attribute __constructor__
 *   @attribute __deconstructor__
 */

typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;
extern uint32_t _kernel_end;
extern void callConstructors(void) {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

int volatile trick1 = 5;
int volatile trick2 = 5;
int volatile trick3 = 0;

void crash_me() {
    trick3 = trick1 / trick2;
}

static inline void kernel_init_early() {
    init_serial_port();
}

/*
 * @function kernelMain:
 *      Main function of the kernel,
 *      the function the GRUB bootloader
 *      calls when Loading the kernel.
 *
 */
void kernelMain(multiboot_info_t* multiboot_structure, uin32_t magicnumber) {
    if (multiboot_structure && magicnumber){};
    init_cpu();
    setup_driver_handler();
    sti();
    kernel_init_early();

    init_desktop(0x7, 0x5);

    while(1)
        hlt();
}

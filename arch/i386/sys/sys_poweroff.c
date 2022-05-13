#include <stdint.h> 
#include <misc/status_codes.h>
#include <misc/asm_util.h>
#include <stddef.h>
#include <io/io.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>

int root_sys_poweroff(void) {
    printck(0x4, 0x0, "SHUTTING DOWN\n");
    sleep(2000);
    __asm__ __volatile__ (
        "out %1, %0"
        :
        : "dw" ((uint16_t)0xB004), "a" ((uint16_t)0x2000)
    );

    return STATUS_OK;
}

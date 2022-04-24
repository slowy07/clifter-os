#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <libc/stdio/stdio.h>
#include <drv/pit/pit.h>
#include <libc/unistd/sleep/sleep.h>
#include <drv/driver.h>
#include <libc/assertk.h>
#include <misc/asm_util.h>

void sleep(uint32_t ms) {
    assertkm(device_initialized(PIT_DRIVER_INDEX), "PIT NOT INITIALIZED");
    int64_t expiry = pit_ticks + ((uint64_t)ms * IRQ_SEC_HIT) / 1000;
    while(pit_ticks < expiry) hlt();
}

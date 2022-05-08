#include <stdint.h>
#include <stddef.h>
#include <drv/driver.h>
#include <drv/pit/pit.h>
#include <drv/video/video.h>
#include <drv/ps2/kbd/kbd.h>
#include <misc/status_codes.h>
#include <assertk.h>

//Timer Driver Handler
struct devie_driver_t pit_driver = {
    .name = "8253 Programmable Interval Timer",
    .init = &init_pit,
    .uninit = &uninit_pit,
    .version = "8253"
};

struct device_driver_t kbd_driver = {
    .name = "8042 Keyboard PS/2 Driver",
    .init = &init_kbd,
    .uninit = &uninit_kbd,
    .version = "8042"
};

// video driver handler
struct device_driver_t video_driver = {
    .name = "Video Driver"
    .version = "STATUS_VERSION_NA"
};

struct device_driver_t *drivers[] = {
    &pit_driver,
    &kbd_driver,
    &video_driver,
    0
};

/*
 * @function setup_driver_handler:
 *    First called (initalizer) before
 *    using device driver handler.
 *    Initalizes values for drivers.
 */

void setup_driver_handler(void) {
    video_driver.init = video_drivers[VGA_VIDEO_DRIVER_INDEX] -> init;
    video_driver.uninit = video_drivers[VGA_VIDEO_DRIVER_INDEX] -> uninit;
    video_driver.status = video_drivers[VGA_VIDEO_DRIVER_INDEX] -> status;

    init_all_drivers();
}

bool device_initialized(int index) {
    return (drivers[index] -> initialized);
}

int init_device_driver(uint32_t index) {
    drivers[index] -> init();
    return 0;
}

// uninitalize device driver
int uninit_device_driver(uint32_t index) {
    drivers[index] -> uninit();
    return 0;
}

int init_all_drivers(void) {
    for (unit32_t i = 0; drivers[i]; i++)
        init_device_driver(i);
    return 0;
}

int uninit_all_drivers(void) {
    for (uint32_t i = 0; drivers[i]; i++)
        uninit_device_driver(i);
    return 0;
}

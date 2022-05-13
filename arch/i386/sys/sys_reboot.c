#include <stdint.h> 
#include <misc/status_codes.h>
#include <misc/asm_util.h>
#include <stddef.h>
#include <io/io.h>
#include <drv/ps2/kbd/kbd.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>

int root_sys_reboot(void) {
    printck(0x4, 0x0, "REBOOTING\n");
    sleep(2000);
    uint8_t _status = 0x02;
    while (_status & 0x02)
        _status = inb(KBD_CTRL_STATS_REG);
    outb(KBD_CTRL_CMD_REG, KBD_ENCODER_CMD_SEND_SYSTEM_REST);
    kbd_ctrl_send_cmd(KBD_CTRL_STATS_MASK_OUT_BUF);
    kbd_enc_send_cmd(KBD_ENCODER_CMD_SEND_SYSTEM_RESET);

    return STATUS_OK;
}

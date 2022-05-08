#include <stdbool.h>
#include <stddef.h>
#include <io/io.h>
#include <drv/ps2/kbd/kbd.h>
#include <drv/ps2/kbd/utils.h>

uint8_t kbd_ctrl_read_status_reg() {
    return (inb(KBD_CTRL_STATUS_REG));
}

void kbd_ctrl_send_cmd(uint8_t cmd) {
    while ((kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) != 0);
    outb(KBD_CTRL_CMD_REG, cmd);
}

/*
 *  Keyboard Encoder :
 * Read encoder input buffer
 * and send command to encoder
 */
uint8_t kbd_enc_read_input_buf() {
    return (inb(KBD_ENC_INPUT_BUF_REG));
}

// send command to encoder
void kbd_enc_send_cmd(uint8_t cmd) {
    while ((kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) != 0);
    outb(KBD_ENC_CMD_REG, cmd);
}

bool bat_test(void) {
    kbd_ctrl_send_cmd(KBD_CTRL_CMD_SELF_TEST);
    while((kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) == 0);

    return (kbd_enc_read_input_buf() == 0x55) ? true : false;
}

bool led_light(bool scroll, bool num, bool caps) {
    uint8_t data_final = 0x0;
    if (scroll) data_final |= KBD_SCROLL_LED_ON;
    if (num) data_final |= KBD_NUM_LED_ON;
    if (caps) data_final |= KBD_CAPS_LED_ON;

    kbd_info.led.num_lock = num;
    kbd_info.led.caps_lock = caps;
    kbd_info.led.scroll_lock = scroll;

    kbd_enc_send_cmd(KBD_ENCORDER_CMD_SET_LED);

    kbd_enc_send_cmd(data_final);

    return true;
}

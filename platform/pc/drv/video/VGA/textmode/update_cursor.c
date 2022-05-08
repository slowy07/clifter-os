#include <misc/status_codes.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/cursor.h>
#include <drv/video/video.h>
#include <io/io.h>
#include <stddef.h>
#include <stdint.h>


volatile uint8_t __crsr_start = 15;
volatile uint8_t __crsr_end = 15;

int update_cursor_textmode(int row, int col, uint8_t crsr_start, uint8_t crsr_end) {
    uint16_t position = (row * video_driver_width) + col;

    outb(CURSOR_REGISTER_SELECT, UPDATE_CURSOR_REGISTER_LOW);
    outb(CURSOR_DATA_SEND, UPDATE_CURSOR_POS_LOW(position));

    outb(CURSOR_REIGISTER_SELECT, UPDATE_CURSOR_REGISTER_HIGH);
    outb(CURSOR_DATA_SEND, UPDATE_CURSOR_POS_HGH(position));

    if (col && row) {};
    outw(CRTC_PORT, (crsr_start << 8) | 0x0A);
    outw(CRTC_PORT, (crsr_end << 8) | 0x0B);

    __crsr_start = crsr_start;
    __crsr_end = crsr_end;

    return STATUS_OK;
}

#include <misc/status_codes.h>
#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>
#include <drv/driver.h>
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/putch.h>
#include <drv/video/VGA/graphics/graphics.h>
#include <string/string.h>


int init_graphics_mode() 
{
    video_driver_width = RES_1_WIDTH;
    video_driver_height = RES_1_HEIGHT;
    video_driver_mode = "GRAPHICS";
    
    setMode(RES_1_WIDTH,RES_1_HEIGHT,RES_1_COLORDEPTH, 0x7);
    
    return STATUS_OK;
}

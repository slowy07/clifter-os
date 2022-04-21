#ifndef _GUI_WIDGET_H_
#define _GUI_WIDGET_H_

#include <stdint.h>

typedef struct
{
    /* data */
    uint8_t color;
    
    uint32_t x;
    uint32_t y;
    
    uint32_t h;
    uint32_t w;

}widget_vga_t;

extern widget_vga_t* createdWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);

#endif // _GUI_WIDGET_H_

#include <io/io.h> 
#include <stdbool.h>
#include <stdio/stdio.h>
#include <drv/video/VGA/graphics/graphics.h>
#include <drv/video/VGA/graphics/resolutions.h>

void writeRegister(uint8_t * register_res); //prototype

bool supports_mode(int width, int height, int colorDepth) {
    return (width == RES_1_WIDTH && height==RES_1_HEIGHT && colorDepth == RES_1_COLORDEPTH);
}

uint8_t* getFramBufferSeg() {
    outb(0x3c, 0x06);
    uint8_t segmentNumber = inb(0x3cf) & (3 << 2);
    switch (segmentNumber) {
        default:
            case 0<<2: return (uint8_t*)0x00000;
            case 1<<2: return (uint8_t*)0xA0000;
            case 2<<2: return (uint8_t*)0xB0000;
            case 3<<2: return (uint8_t*)0xB8000;
    }
}

void vgaGraphicsPutPixel(int32_t x, int32_t y, uint8_t colorIndex ) {
    if (x < 0 || RES_1_WIDTH <= x || y < 0 || RES_1_HEIGHT <= y) {
        return;
    }
    uint8_t* pixelAddress = getFramBufferSeg() + RES_1_WIDTH * y + x;
    *pixelAddress = colorIndex;
}

void fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t colorHex) {
    for (uint32_t Y = y; Y < y+h; Y++) {
        for (uint32_t X = x; X < x+w; X++) {
            vgaGraphicsPutPixel(X, Y, colorHex);
        }
    }
}

void setMode(int width, int height, int colorDepth, uint8_t background) {
    bool support = supports_mode(width, height, colorDepth);
    if (support == false) {
        printck(8, 0, "NOT SUPPORTED RESOLUTION.\n");
        return;
    }
    if (width == RES_1_WIDTH && height == RES_1_HEIGHT && colorDepth == RES_1_COLORDEPTH)
        writeRegister(g_320x200x256);

    fillRectangle(0, 0, RES_1_WIDTH, RES_1_HEIGHT, background);
}

void clearVgaGraphics() {
    fillRectangle(0, 0, RES_1_WIDTH, RES_1_HEIGHT, 0x0);
}

void writeRegister(uint8_t* register_res) {
    // misc
    outb(0x3c2, *(register_res++));

    for (uint8_t i = 0; i < 5; i++) {
        outb(0x3c4, i);
        outb(0x3c5, *(register_res++));
    }

    // cathode ray tube controller
    outb(0x3d4,0x03);
    outb(0x3d5,inb(0x3d5) | 0x80);
    outb(0x3d4,0x11);
    outb(0x3d5,inb(0x3d5) & ~0x80);

    register_res[0x03] = register_res[0x03] | 0x80;
    register_res[0x11] = register_res[0x11] & ~0x80;

    for(uint8_t i = 0; i < 25; i++) {
        outb(0x3d4,i);
        outb(0x3d5,*(register_res++));
    }

    // graphics controller
    for(uint8_t i = 0; i < 9; i++) {
        outb(0x3ce,i);
        outb(0x3cf,*(register_res++));
    }

    // attribute controller
    for(uint8_t i = 0; i < 21; i++) {
        inb(0x3da);
        outb(0x3c0,i);
        outb(0x3c0,*(register_res++));
    }

    inb(0x3da);
    outb(0x3c0,0x20);
}

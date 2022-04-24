#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#include <libc/stdio/printk/printk.h>
#include <drv/video/video.h>
#include <libc/stdlib/itoa/itoa.h>
#include <libc/math/powk/powk.h>

#include <string/string.h>

extern volatile uint8_t __crsr_start;
extern volatile uint8_t __crsr_end;


void printk(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vprintk(fmt, arg);
    va_end(arg);
}

void vprintk(const char* fmt, va_list arg) {
    if (strcmp(video_driver_mode, "GRAPHICS") == 0) {
        return;
    }
    int integer_format;
    int after_decimal;
    float float_format;
    char *result_pt = " ";
    
    int int_part;
    int multiplier;
    int float_prt;
    int digit;

    for (int i = 0; fmt[i] != '\0'; i++) {
        switch(fmt[i]) {
            case '%':
                switch(fmt[i+1]) {
                    case 'd':
                        integer_format = var_arg(arg, int);
                        result_pt = itoa(integer_format);
                        for(int x = 0; result_pt[x] != '\0'; x++) {
                            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> putch(result_pt);
                            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor
                            (video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_row, video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column
                            ,__crsr_start, __crsr_end);
                        }
                        i += 1;
                        break;
                    case 'c':
                        video_drivers[VGA_VIDEO_DRIVER_INDEX] -> putch(va_arg(arg, int));

                        video_drivers[VGA_DRIVER_INDEX] -> update_cursor
                        (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                        ,__crsr_start,__crsr_end);
                        i += 1;
                        break;
                    case 's':
                        result_pt = va_arg(arg, char*);
                        for (int x = 0; result_pt[x]; x++) {
                            printk("%c", result_pt[x]);
                        }
                        i += 1;
                        break;
                    case 'x':
                        integer_format = va_arg(arg, int);
                        __itoa(integer_format, 16, result_pt);
                        for (int x = 0; result_pt[x] != '\0'; x++) {
                            video_drivers[VGA_VIDEO_DRIVER_INDEX] -> putch(result_pt[x]);
                            video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
                            (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                            ,__crsr_start,__crsr_end);
                        }
                        i += 1;
                        break;
                    case '.':
                        after_decimal = fmt[i+2] - '0';
                        switch(fmt[i+3]) {
                            case 'f':
                                float_format = va_arg(arg, double);
                                int_part = (int)float_format;
                                printk("%d", int_part);

                                if (after_decimal) {
                                    printk(".");
                                    multiplier = powk(10, after_decimal - 1);
                                    float_part = float_format * (multiplier * 10);

                                    while (multiplier) {
                                        digit = float_part / multiplier % 10;
                                        printk("%d", digit);
                                        multiplier /= 10;
                                    }
                                }

                                break;
                        }
                        video_drivers[VGA_DRIVER_INDEX] -> update_cursor
                        (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                        ,__crsr_start,__crsr_end);
                        i += 3;
                        breakl
                }

            case '\n':
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_row++;
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column = 0;
                
                video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
                (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                ,__crsr_start,__crsr_end);
                break;
            case '\b':
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column--;
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> putch(' ');
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column--;
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor
                (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                ,__crsr_start,__crsr_end);
                break;
            case '\t':
                for(int32_t t = 0; t <= 3; t++) video_drivers[VGA_VIDEO_DRIVER_INDEX] -> video_column++;
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor
                (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                ,__crsr_start,__crsr_end);
                break;
            case '\\':
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> putch('\\');
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor
                (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                ,__crsr_start,__crsr_end);
                break;
            default:
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> putch(fmt[i]);
                video_drivers[VGA_VIDEO_DRIVER_INDEX] -> update_cursor
                (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column
                ,__crsr_start,__crsr_end);
                break;
        }
    }
}
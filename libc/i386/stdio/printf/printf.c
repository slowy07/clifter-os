#include "printf.h"

extern void putchar(char c);

size_t terminal_column=0;
size_t terminal_row=0;
uint8_t FG = 0x7;
uint8_t BG = 0x0;

extern void __itoa(unsigned i, unsigned base, char* buf);
extern char *itoa(int val);

void printf(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    int integer_format;
    char *result_pt=" ";

    for(int i=0; fmt[i]!= '\0'; i++) {
        switch(fmt[i]){
            case '%':
                switch(fmt[i+1]){
                    case 'd':
                        integer_format = va_arg(arg, int);
                        result_pt = itoa(integer_format);
                        for(int i=0; result_pt[i]!= '\0'; i++)
                            putchar(result_pt[i]);
                        i+=1;
                        break;
                    case 'c':
                        putchar(va_arg(arg,int));
                        i+=1;
                        break;
                    case 's':
                        result_pt = va_arg(arg, char*);
                        for(int i=0;result_pt[i]!='\0'; i++)
                            putchar(result_pt[i]);
                        i+=1;
                        break;
                    case 'x':
                        integer_format = va_arg(arg, int);
                        __itoa(integer_format, 16, result_pt);
                        for(int i=0; result_pt[i]!='\0';i++)
                            putchar(result_pt[i]);
                        i+=1;
                        break;
                }
                break;
            case '\n':
                terminal_row++;
                terminal_column=0;
                break;
            case '\b':
                terminal_column--;
                break;
            case '\t':
                for(int32_t t=0; t <= 3; t++) terminal_column++;
            default:
                putchar(fmt[i]);
                break;
        }
    }

    va_end(arg);
}
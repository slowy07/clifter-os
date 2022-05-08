#include <cpu/interrupts/interrupts.h>
#include <misc/status_codes.h>
#include <libc/stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/pit/pit.h>
#include <io/io.h>
#include <stdint.h>
#include <stddef.h>


struct device_driver_t pcspkr_driver = {
    .name = "PC_SPEAKER",
    .version = "STATUS_VERSION_NA",
    .init = &pcspkr_init,
    .uninit = &pcspkr_uninit,
};

/*
 * @function send_msg_counter_2:
 *   Send message to Counter 2(Channel) ,
 *   where the PC Speaker is located ,
 *   for the 8254 PIC Intel Microcontroller.
 */

void send_msg_counter_2 (uint8_t cmd) {
    outb(I386_PIT_COUNTER_2_REG, cmd);
}

/*
 * @function send_msg_counter_2:
 *   Send message to Counter 2(Channel) ,
 *   where the PC Speaker is located ,
 *   for the 8254 PIC Intel Microcontroller.
 */

void set_freq_pcspkr(uint32_t freq) {
    uint32_t __div;

    __div = I386_PIT_OSCILLTOR_CHIP_FREQ / freq;
        outb(0x43, I386_PIT_OCW_BINCOUNT_BINARY |
            I386_PIT_OCW_MODE_SQUAREWAVEGEN |
            I386_PIT_OCW_RL_DATA |
            I386_PIT_OCW_SCO_COUNTER_2);
        send_msg_counter_2((uint8_t)(__div));
        send_msg_counter_2((uint8_t)(__div>>8));
}

void pc_speaker_silent() {
    uint32_t pcspkr = inb(I86_PC_STTUS_REG)&I86_PC_SPKR_DISABLE;
    outb(0x61,pcspkr);
}

/*
 * @function pcspkr_beep :
 *    Makes the PC Speaker
 *    beep.
 *    
 *    @param freq : Frequency given
 *                  for speaker to beep.
 */

int pcspkr_beep(uint32_t freq) {
    if (pcskpr_driver.initialized == true) {
        set_freq_pcspkr(freq);
        uint8_t pcspkr = inb(I86_PC_SSPKR_STATUS_REG);
        if (pcskpr != (pcskpr | I86_PC_SPKR_ENABLE))
            // if pc speaker not already set
            outb(0x61, pcspkr | I86_PC_SPKR_ENABLE);
    }
    else
        printk("pc speaker not initalized or uninitialized");
    return STATUS_OK;
}

int pcspkr_init() {
    pcspkr_driver.initalized = true;
    return STATUS_OK;
}

int pckspkr_uninit() {
    pcspkr_driver.initalized = false;
    return STATUS_OK;
}

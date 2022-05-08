#include <cpu/interrupts/interrupts.h>
#include <misc/status_codes.h>
#include <cpu/interrupts/irq.h>
#include <libc/unistd/sleep/sleep.h>
#include <libc/stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/driver.h>
#include <drv/pit/pit.h>
#include <io/io.h>
#include <stdint.h>
#include <stddef.h>


// time driver handler

struct device_driver_t pit_driver = {
    .name = "8253 Programmable Interval Timer",
    .init = &init_pit,
    .uninit = &uninit_pit,
    .version = "8253"
};

volatile uint32_t pit_ticks = 0;

void send_pit_command(uint8_t cmd) {
    outb(I386_PIT_CONTROL_WORD_REG, cmd);
}

/*
 * @function send_msg_counter_0:
 *    Sends Messages to Counter
 *    0 of PIT's Internal Registers.
 *    Counter 0 sets registers
 */

void send_msg_counte_0(uint8_t cmd) {
    outb(I386_PIT_COUNTER_0_REG, cmd);
}

/*
 * @function pit_phase:
 *    Initalizes the PIT Intenally
 *    with the number of IRQ's per
 *    second specified.
 */

static void pit_phase(int htz) {
    //1.19MHz / htz
    //dictates how any times
    //the IRQ Should fire
    int divisor = I386_PIT_OSCILLATOR_CHIP_FREQ / htz;
    
    send_pit_command(I386_PIT_OCW_BINCOUNT_BINARY |
                     I386_PIT_OCW_MODE_SQUAREWAVEGEN |
                     I386_PIT_OCW_RL_DATA |
                     I386_PIT_OCW_SCO_COUNTER_0);
    send_msg_counter_0(divisor & 0xFF);
    send_msg_counter_0(divisor >> 8);
}

/*
 * @function pit_handler_nest :
 *    Functions that gets called
 *    every time PIT IRQ Fires.
 *
 *      @return int:
 *      @if 0 == RETURN_OK
 *      @if !0 == RETURN_ERROR
 */

static int pit_handler_nest() {

    //printk("%d SECONDS\n", (pit_ticks/IRQ_SEC_HIT));
    return 0;
}

static void pit_handler(int_regs *r) {
    if (r){};
    pit_ticks++;
    if (pit_ticks % IRQ_SEC_HIT == 0) {
        if (pit_handler_nest() != 0) {
            panik("PIT handler nest exception");
        }
    }
}

/*
 * @function init_pit:
 *    Initalizes the Programmable
 *    interrupt controller, and installs
 *    the IRQ For PIT.
 */

int init_pit() {
    pit_driver.initialized = true;
    pit_driver.status = STATUS_DRIVER_OK;
    pit_phase(IRQ_SEC_HIT);
    install_irq_handler(IRQ_PIT, pit_handler);
    
    return STATUS_OK;
}
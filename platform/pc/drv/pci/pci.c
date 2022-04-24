#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <io/io.h>
#include <drv/pci/pci.h>
#include <stdio/stdio.h>

// pci device info
multiple_pci_device_t pci_devices;

/**
  * Get adress to send to CONFIG_PORT
  * via I/O.
  */

static inline uint32_t pci_get_address(uint32_t bus, uint32_t slot, uint32_t func, uint8_t offset) {
    return (
        (uint32_t)
        (
            (bus << 16) | (slot << 11) |
            (func << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)
        )
    );
}

void write_config_address(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus = (uint32_t)bus; // long bus(32bit pad)
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    address = pci_get_address(lbus, lslot, lfunc, offset);
    outd(PORT_CONFIG_ADDRESS, address); // 32bit I/O stream
}

uint16_t read_data(uint8_t offset) {
    uint16_t tmp = 0; // init + declare
    tmp = (uint16_t) (ind(PORT_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff;
    return tmp;
}

uint16_t write_address_read_data(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset) {
    write_config_address(bus,slot,func,offset);
    uint16_t tmp = read_data(offset);
    return tmp;
}

pci_descriptor_header00h_t get_descriptor(uint16_t bus, uint16_t device, uint16_t function) {
    pci_descriptor_header00h_t pdt;

    pdt.bus = bus;
    pdt.device = device;
    pdt.function = function;

    // 0x00 = Vendor ID -- VENDOR (0x8086 = Intel)
    // 0x02 = Device ID -- Diffrent to all specific Devices (0x7000 = ISA To PCI Storage Controller)
    // 0x0B = Class ID  -- Class Identifier = (0x1 = Mass Storage Controller)
    // 0x0A = SubClass ID -- Subclass from Class = (0x1 = IDE Controller)
    // 0x09 = Interface ID -- Subclass specific interface seperation

    // 0x08 = Revision
    // 0x3C = Interrupt

    pdt.vendor_id = write_address_read_data(bus, device, function, 0x00);
    pdt.device_id = write_address_read_data(bus, device, function, 0x02);
    pdt.class_id = write_address_read_data(bus, device, function, 0x0B);
    pdt.subclass_id = write_address_read_data(bus, device, function, 0x0A);
    pdt.interface_id = write_address_read_data(bus, device, function, 0x09);
    pdt.revision_id = write_address_read_data(bus, device, function, 0x08);
    pdt.interrupt = write_address_read_data(bus, device, function, 0x3C);
    pdt.cache_line_size = write_address_read_data(bus, device, function, 0xF);

    return pdt;
}

bool device_has_func(uint16_t bus, uint16_t device) {
    return write_address_read_data(bus, device, 0, 0x0E) & (1 << 7);
}

multiple_pci_device_t fill_pci_devices() {
    int counter_pci_device = 0;
    for (int bus = 0; bus < 8; bus++) {
        for (int device = 0; device < 32; device++) {
            int num_func = device_has_func(bus, device);
            
            for (int func = 0; func < num_func; func++) {
                pci_descriptor_header00h_t pci_head = get_descriptor(bus, device, func);

                if (pci_head.vendor_id != 0xFFFF & pci_head.device_id != 0xFF) {
                    pci_devices.pci_device[counter_pci_device].vendor_id = pci_head.vendor_id;
                    pci_devices.pci_device[counter_pci_device].class_id = pci_head.class_id;
                    pci_devices.pci_device[counter_pci_device].subclass_id = pci_head.subclass_id;
                    pci_devices.pci_device[counter_pci_device].device_id = pci_head.device_id;

                    pci_devices.pci_device[counter_pci_device].bus = bus;
                    pci_devices.pci_device[counter_pci_device].function = func;
                    counter_pci_device++;
                }
            }
        }
    }
    return pci_devices;
}

void print_pci_devices_enumeration_scheme() {
    printk("-----pci devices------\n");
    printk("VENDOR\tDEVICE\tCLASS\tDEVICE_ID\n");

    for (int bus = 0; bus < 256; bus++) {
        for (int device = 0; device < 32; device++) {
            int num_func = device_has_func(bus, device);
            
            for (int func = 0; func < num_func; func++) {
                pci_descriptor_header00h_t pci_head = get_descriptor(bus, device, func);

                if(pci_head.vendor_id != 0xFFFF && pci_head.device_id != 0xFF)
                    printk("0x%x\t0x%x\t0x%x\t0x%x\n" , pci_head.vendor_id, pci_head.device_id, pci_head.class_id,pci_head.subclass_id);
            }
        }
    }
}

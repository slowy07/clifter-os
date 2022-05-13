#include <cpu/cpuid.h>
#include <var/cpu/cpu_info.h>
#include <misc/status_codes.h>
#include <string/string.h>
#include <stdio/stdio.h>

cpu_info_t cpu_info;

static const char* vendor_id_string[] = {
    "GenuineIntel",
    "AMDisbetter!",
    "AuthenticAMD",
    "CentaurHauls",
    "CyrixInstead",
    "TransmetaCPU",
    "GenuineTMx86",
    "Geode by NSC",
    "NexGenDriven",
    "RiseRiseRise",
    "SiS SiS SiS ",
    "UMC UMC UMC ",
    "VIA VIA VIA ",
    "Vortex86 SoC",
    "KVMKVMKVM",
    "Microsoft Hv",
    "VIA VIA VIA ",
    "VMwareVMware",
    " lrpepyh vr"
};

static const char* vendor_company_strings[] = {
    "Intel",
    "K5-AMD",
    "AMD",
    "Centaur",
    "Cyrix",
    "Transmeta",
    "Transmetax86",
    "National Semiconductor",
    "NexGen",
    "Rise",
    "SiS",
    "UMC ",
    "VIA ",
    "Vortex86",
    "KVM",
    "Microsoft Hypervisor",
    "VIA",
    "VMware",
    "Parrelels"
};

static inline void find_comp(char* ID) {
    for (int i = 0; vencor_id_strings[i]; i++) {
        if (strcmp(ID, vendor_id_strings[i]) == 0) {
            cpu_info.companyName = (char*) vendor_company_strings[i];
            return;
        }
    }
    cpu_info.companyName = "Unknowwn";
}

static void signature_processing(uint32_t sig) {
    if (strcmp(cpu_info.companyName, "Intel") == 0) {
        int bit_twelve = (sig >> 12) & 1;
        int bit_thirteen = (sig >> 13) & 1;
        if (bit_twelve == 0 && bit_thirteen == 0)
            cpu_info.processor_type = "Original OEM Processor";
        else if (bit_twelve == 0 && bit_thirteen == 1)
            cpu_info.processor_type = "OverDrive Processor";
        else if (bit_twelve == 1 && bit_thirteen == 0)
            cpu_info.processor_type = "Dual Processor";
        else if (bit_twelve == 1 && bit_thirteen == 1)
            cpu_info.processor_type = "Intel Reserved".
        else 
            cpu_info.processor_type = "Unknown";
    }
}

int init_cpu_info() {
    cpu_info.vendorID = (char*) cpu_id.vendorID;
    cpu_info.ecx_features = cpu_id.features_ecx;
    cpu_info.edx_features = cpu_id.features_edx;
    cpu_info.signature = cpu_id.signature;
    find_comp(cpu_info.vendorID);
    signature_processing(cpu_info.singature);

    return STATUS_OK;
}

void __debug_print_cpu_info() {
    #ifdef DEBUG
        printk("CPU\n");
        printk("--\n");
        printk("COMPANY : %s\n", cpu_info.companyName);
        printk("VENDOR_ID : %s\n", cpu_info.vendorID);
        printk("PROCESSOR TYPE: %s\n", cpu_info.processor_type);
    #endif
}

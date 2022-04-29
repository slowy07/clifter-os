section .text

    extern interupt_handler

    %macro interupt_m_code 1
        global int%1
        int%1:
            cli
            push %1
            jmp int_service
    %endmacro

    %macro interupt_m_nocode 1
        global int%1
        int%1:
            cli
            push 0
            push %1
            jmp int_service
    %endmacro

    int_service:
        push eax
        push ecx
        push edx
        push ds
        push esp
        call interupt_handler
        pop eax
        pop ds
        pop edx
        pop ecx
        pop eax
        add esp, 8
        iret
    
    %include "../../../shared/x86/cpu/interrupts/isr.asm"
    %include "../../../shared/x86/cpu/interrupts/irq.asm"
    
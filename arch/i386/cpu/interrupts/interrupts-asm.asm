section .text
    extern interrupt_handler
    %macro interrupt_m_code 1
        global int%1
        int%1:
            cli
            push %1
            jmp int_service
    %endmacro

    %macro interrupt_m_nocode 1
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
        call interrupt_handler
        pop eax
        pop ds
        pop edx
        pop ecx
        pop eax
        add esp, 8
        iret
    
    %include "isr.asm"
    %include "irq.asm"
    
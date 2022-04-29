section .text
    
    extern interupt_handler

    %macro  interupt_m_code 1
        global int%1
        int%1 :
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



    int_service :
        push rax
        push rbx
        push rcx
        push rdx
        push rsi
        push rdi
        push rbp
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15

        mov rax,0x0010001000100010
        push rax

        mov rax,rsp
        and rsp,-16
        sub rsp,512
        fxsave [rsp]

        push rsp
        push rax

        mov rdi,rsp
        call interupt_handler

        pop rax
        pop rcx
        fxrstor [rcx]
        mov rsp,rax

        pop rax

        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rbp
        pop rdi
        pop rsi
        pop rdx
        pop rcx
        pop rbx
        pop rax

        add esp,16
        iretq

    %include "../../../shared/x86/cpu/interrupts/isr.asm"
    %include "../../../shared/x86/cpu/interrupts/irq.asm"

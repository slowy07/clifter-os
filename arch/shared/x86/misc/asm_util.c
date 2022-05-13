void sti(void) {
    __asm__ __volatile__ ("sti");
}

void cli(void) {
    __asm__ __volatile__ ("cli");
}

void hlt(void) {
    __asm__ __volatile__ ("hlt");
}

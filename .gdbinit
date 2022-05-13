add-auto-safe-path /mnt/c/Users/aboga/ClifterOS/.gdbinit
file ClifterOS.bin
target remote localhost:1234
symbol-file ClifterOS.bin
win
b kernelMain
c

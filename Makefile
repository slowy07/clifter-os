BUILDROOT := $(realpath .)
export BUILDROOT

include config/ARCH.mk
include config/PLAT.mk

GENERATED_CONFIG := config/GENERATED_CONFIG.mk
ifndef GENERATED_CONFIG
 -include $(GENERATED_CONFIG)

 LIBGCC := $(shell $(CC) $(ARCH_MACHINE) -print-libgcc-file-name)
 LIBGCCDIR := $(dir $(LIBGCC))
 LIBGCCFILENAME := $(notdir $(LIBGCC))
 LIBGCCNAME := $(patsubst lib%.a,%,$(LIBGCCFILENAME))
endif

ifdef CROSSROOT
	$(shell echo $(CROSSROOT) > Makefile.cached.CROSSROOT)
else
	ifneq (, $(wildcard Makefile.cached.CROSSROOT))
		CROSSROOT := $(shell cat Makefile.cached.CROSSROOT)
	endif
endif


ifdef CROSSROOT
	HOST_ENV = $(shell uname -p)
	
	CROSSROOT ?= $(BUILDROOT)/cross
	CC := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-gcc
	LD := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-ld
	AR := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-ar
	export CC
	export LD
	export AR
endif

IDEO_DRIVER := VGA
VIDEO_DRIVER_LOW := vga
VIDEO_DRIVER_MODE := textmode
VIDEO_DRIVER_RES_W := 80
VIDEO_DRIVER_RES_H := 25
VIDEO_DRIVER_RES := $(VIDEO_DRIVER_RES_W)x$(VIDEO_DRIVER_RES_H)
export VIDEO_DRIVER
export VIDEO_DRIVER_LOW
export VIDEO_DRIVER_RES_W
export VIDEO_DRIVER_RES_H
export VIDEO_DRIVER_RES
export VIDEO_DRIVER_MODE

# Programs
BOCHS := bochs
QEMU := qemu-system-$(ARCH_QEMU)
PYTHON := python
SH := sh
VB := virtualbox
VBM := VBoxManage
GDB := gdb_q



INCDIRS := $(BUILDROOT)/include \
    $(BUILDROOT)/arch/$(ARCH)  \
    $(BUILDROOT)/include/arch/$(ARCH) \
    $(BUILDROOT)/include/apps \
    $(BUILDROOT)/include/bin \
    $(BUILDROOT)/include/sbin \
    $(BUILDROOT)/include/libc \
    $(BUILDROOT)/include/platform/$(PLAT) \
    $(BUILDROOT)/include/libc/string \
    $(BUILDROOT)/include/arch/shared/x86 \

# Parameters
LDPARAMS := -melf_$(ARCH_LINKER) --build-id=none
CFLAGS := \
	$(ARCH_MACHINE) -std=c11 \
	-O0 -g -Wall -Wextra -Wpedantic -Werror  -g \
	-Wno-error=missing-field-initializers \
	-nostdlib -ffreestanding $(patsubst %,-I%,$(INCDIRS))

ASFLAGS := $(ARCH_AS_FLAGS)

NASM ?= nasm
NASMFLAGS := -f elf32

export CFLAGS
export LDFLAGS
export NASM
export NASMFLAGS

CLIFTEROS_ISO := ClifterOS.iso
CLIFTEROS_BIN := ClifterOS.bin
CLIFTEROS_BOOT_DIR := boot/boot
CLIFTEROS_BOOT_BIN := $(CLIFTEROS_BOOT_DIR)/$(CLIFTEROS_BIN)
CLIFTEROS_GRUB_CFG := $(CLIFTEROS_BOOT_DIR)/grub/grub.cfg
LINKER_SCRIPT := arch/$(ARCH)/link/linker.ld

SCRIPT_CC := utils/cross_compiler/toolchain.py


libraries = \
	libc/libc.a \
	arch/$(ARCH)/libarch.a \
	apps/libapps.a \
	bin/libbin.a \
	sbin/libsbin.a \
	arch/shared/$(ARCH_FAMILY)/libshared_arch.a \
	platform/$(PLAT)/libplatform.a
export libraries

# standar targets

all: iso

clean: clean-subdirs
	rm -f (CLIFTEROS_ISO)
	rm -rf iso

.PHONY: all clean

$(libraries): subdirs

subdirs:
	(cd libc && $(MAKE))
	(cd arch && $(MAKE))
	(cd apps && $(MAKE))
	(cd bin  && $(MAKE))
	(cd sbin && $(MAKE))
	(cd platform && $(MAKE))

clean-subdirs:
	(cd libc && $(MAKE) clean)
	(cd arch && $(MAKE) clean)
	(cd apps && $(MAKE) clean)
	(cd bin  && $(MAKE) clean)
	(cd sbin && $(MAKE) clean)
	(cd platform && $(MAKE) clean)

.PHONY: subdirs clean-subdirs

$(CLIFTEROS_BIN) $(libraries) $(LINKER_SCRIPT)
	$(LD) $(LDPARAMS) \
	-T $(LINKER_SCRIPT) \
	-o $@ \
	--start-group $(libraries) --end-group \
	-L$(LIBGCCDIR) -l$(LIBGCCNAME)

$(CLIFTEROS_BOOT_BIN): $(CLIFTEROS_BIN)
	mkdir -p $(dir $(CLIFTEROS_BOOT_BIN))
	cp $(CLIFTEROS_BIN) $(CLIFTEROS_BOOT_BIN)

$(CLIFTEROS_ISO): $(CLIFTEROS_BOOT_BIN)
	cp ClifterOS.bin boot/boot/ClifterOS.bin
	grub-mkrescue --output=ClifterOS.iso boot

iso: $(CLIFTEROS_ISO)

# get toolchain
$(COMPILER): get-toolchain

get-toolchain:
	$(PYTHON) utils/cross_compiler/toolchain.py

.PHONY: iso

no_vnc:
	$(SH) utils/novnc/install.sh
	$(SH) utils/novnc/run.sh

.PHONY: no_vnc

gdb_q: $(CLIFTEROS_BIN)
	$(QEMU) -kernel $(CLIFTEROS_BIN) -display sdl -s -S

debug_q:
	$(GDB) --symbols=$(CLIFTEROS_BIN) --tui \
		-iex 'set architecturei386:x86-64' \
		-ex 'target remote localhost:1234' \
		-ex 'layout regs' \
		-ex 'set radix 16' \

qemu_compile: $(CLIFTEROS_BIN)
	$(QEMU) -kernel $(CLIFTEROS_BIN) -display sdl -k en-us -s

qemu_iso: $(CLIFTEROS_BIN) $(CLIFTEROS_ISO)
	$(QEMU) -cdrom $(CLIFTEROS_ISO) -k en-us -s

bochs: $(CLIFTEROS_ISO)
	$(BOCHS) -f bochsrc.bxrc -q

new_line:
	find . \( -name "*.asm" -o -name ".h" -o -name "*.c") -print0 | \
		xargs -0 -iFile sh -c 'echo >> FILE'

custom:	
	xterm -fg white -bg black
	unset TMUX

distclean: clean
	rm -rf $(GENERATED_CONFIG)

configure-help:
	@echo ''
	@echo 'Usage: configure [options]'
	@echo 'Options: [defaults in brackers after description]'
	@echo ''
	@echo '--cc=CC	use C compiler [$(CC)]'
	@echo '--arch=ARCH	compile kernel that runs on ARCH'
	@echo '				available ARCH: x86, x86-64'
	@echo '--plate=PLAT	compile kernel is of platform PLAT'
	@echo '				available PLAT: pc'
	@echo ''

configure-set:
	@echo '# this file automatically generated ' > $(GENERATED_CONFIG)
	@echo '# invoke the configure script to make changes' >> $(GENERATED_CONFIG)
	@echo "CC := $(CC)" >> $(GENERATED_CONFIG)
	@echo "ARCH := $(ARCH)" >> $(GENERATED_CONFIG)
	@echo "PLAT := $(PLAT)" >> $(GENERATED_CONFIG)
	@echo "export CC" >> $(GENERATED_CONFIG)
	@echo "export ARCH" >> $(GENERATED_CONFIG)
	@echo "export PLAT" >> $(GENERATED_CONFIG)
	@echo '' >> $(GENERATED_CONFIG)

.PHONY: gdb_q qemu_compile bochs qemu_iso custom new_line distclean configure-help configure-set

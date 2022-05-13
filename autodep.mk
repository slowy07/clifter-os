.PHONY: all clean

DEPDIR := .d

$(shell mkdir -p $(DEPDIR) >/dev/null)

DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$(notdir $*).Td

DEPFLAGS.nasm = -MD $(DEPDIR)/(notdir $*).Td

OUTPUT_OPTION = -o $@

# Compile commands for C and C++
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION) -c
COMPILE.s = $(AS) $(ASFLAGS) $(TARGET_ARCH_AS) $(OUTPUT_OPTION) -c
COMPILE.asm = $(NASM) $(NASMFLAGS) $(TARGET_ARCH_NASM)
COMPILE.as = $(AS) $(DEPFLAGS) $(ASFLAGS) $(OUTPUT_OPTION) -c


POSTCOMPILE = mv -f $(DEPDIR)/$(notdir $*).Td $(DEPDIR)/$(notdir $*).d

.s.o:
	$(COMPILE.as) $<

.asm.o:
	$(COMPILE.asm) $(OUTPUT_OPTION) $(DEPFLAGS.nasm) $<
	$(POSTCOMPILE)

.c.o:
	$(COMPILE.C) $<
	$(POSTCOMPILE)

.SUFFIXES: .asm

ifdef DISASSEMBLEFLAGS

$(DUMPDIR)/%.dis : $(BINDIR)/%.bin
$(DUMPDIR)/%.dis : $(BINDIR)/%.bin
	objdump $(DISASSEMBLEFLAGS) $< >$@
endif

# Hex Dump
$(DUMPDIR)/%.hex : $(BINDIR)/%.bin
$(DUMPDIR)/%.hex : $(BINDIR)/%.bin
	hexdump -C $< > $@

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(CSRCS))))

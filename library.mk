LIBFILENAME := lib$(LIBNAME).a

# Determine object file filenames
AOBJS := $(ASRCS:.s=.o)
NOBJS := $(NSRCS:.asm=.o)
COBJS := $(CSRCS:.c=.o)

OBJS := $(AOBJS) $(COBJS) $(NOBJS)

all: $(LIBFILENAME)

clean:
	rm -f $(OBJS)
	rm -f $(LIBFILENAME)
	rm -r .d

$(LIBFILENAME): $(OBJS)
	ar -rcs $@ $^

include $(BUILDROOT)/autodep.mk
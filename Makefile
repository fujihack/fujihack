-include config.mak

# Used to get the top level, if in subdir
TOPL?=.

RUSTC=rustc
RM=rm -rf
CP=cp
PYTHON3=python3
CD=cd

ARMCC?=arm-none-eabi

# Add multiple locations to find GCC and libc libs
ARMCCLOC=/home/$(USER)/gcc-arm-none-eabi-5_4-2016q3
ARMLDFLAGS+=-L$(ARMCCLOC)/arm-none-eabi/lib -L$(ARMCCLOC)/lib/gcc/arm-none-eabi/5.4.1
ARMLDFLAGS+=-L/usr/lib/arm-none-eabi/newlib/ -L/usr/lib/gcc/arm-none-eabi/10.3.1/

# Different msg if in different dir
ifeq ($(TOPL),.)
help:
	@echo "Can be built in src/ or minimal/"
else
help:
	@echo "Targets: hack hack.bin"
endif

clean:
	$(RM) *.elf *.o *.bin $(TOPL)/src/*.elf $(TOPL)/src/*.o $(TOPL)/src/*.bin $(TOPL)/frontier/core/*.o $(TOPL)/frontier/mjs/*.o

ifndef model
$(error define model via CLI or by config.mak)
endif

ifdef WIN
FUJI_OUT=fuji.exe
else
FUJI_OUT=fuji
endif

build-fuji:
	$(CD) $(TOPL)/ptp && $(MAKE) $(FUJI_OUT)

build-frontier:
	$(CD) $(TOPL)/frontier/tool && $(MAKE)

# phony target to load hack onto camera (PTP/USB)
hack: build-fuji hack.bin
	$(TOPL)/ptp/$(FUJI_OUT) -r hack.bin

# Changing any of these could make compilation different
EXTERN_DEPS=Makefile ../model/$(model).h $(wildcard ../patch/*) $(wildcard *.h)

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# stub.S is compiled with stubs from model header file
stub.o: stub.S ../model/$(model).h
	$(ARMCC)-gcc -D FPIC -D STUBS $(ARMCFLAGS) $< -o $@

# Support rust files -> emit ARM asm -> regular ELF files
# TODO: armv7a-none-eabi may be better
RARCH=armv5te-unknown-linux-musleabi
RFLAGS=-C opt-level=2 --target $(RARCH) --emit obj --crate-type rlib
%.o: %.rs $(EXTERN_DEPS) $(wildcard *.rs)
	$(RUSTC) $(RFLAGS) $< -o $@

.PHONY: hack help clean run build-fuji

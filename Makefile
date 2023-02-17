-include config.mak

# Used to get the top level, if in subdir
TOPL?=.

RUSTC=rustc
RM=rm -rf
CP=cp
PYTHON3=python3

ARMCC?=arm-none-eabi

# Different msg if in different dir
ifeq ($(TOPL),.)
help:
	@echo "Can be built in src/ or minimal/"
clean:
	$(RM) src/*.elf src/*.o src/*.bin minimal/*.elf minimal/*.o minimal/*.bin
else
help:
	@echo "Targets: hack hack.bin"
clean:
	$(RM) *.elf *.o *.bin ../src/*.elf ../src/*.o ../src/*.bin
endif

ifndef model
$(error define model via CLI or by config.mak)
endif

ifdef WIN
FUJI_OUT=fuji.exe
else
FUJI_OUT=fuji
endif

build-fuji:
	cd $(TOPL)/ptp && $(MAKE) $(FUJI_OUT)

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

.PHONY: hack help clean run

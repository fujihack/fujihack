-include config.mak

model?=xf1_101

# Used to get the top level, if in subdir
TOPL?=.

RM=rm -rf
CP=cp
PYTHON3=python3

ARMCC?=arm-none-eabi

# Different msg if in different dir
ifeq ($(TOPL),.)
help:
	@echo "Can be built in src/ or minimal/"
else
help:
	@echo "Targets: hack hack.bin"
endif

# phony target to load hack onto camera
hack: hack.bin
	$(PYTHON3) $(TOPL)/ptp/load.py -l hack.bin

# Changing any of these could make compilation different
EXTERN_DEPS=Makefile $(TOPL)/model/$(model).h *.h $(wildcard $(TOPL)patch/*)

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# stub.S is compiled with stubs from model header file
stub.o: stub.S ../model/$(model).h
	$(ARMCC)-gcc -D FPIC -D STUBS $(ARMCFLAGS) $< -o $@

RARCH=armv5te-unknown-linux-musleabi
RFLAGS=-C opt-level=2 --target $(RARCH) --emit asm --crate-type rlib
%.o: %.rs $(EXTERN_DEPS)
	rustc $(RFLAGS) $< -o $<.s
	$(ARMCC)-gcc $(ARMCFLAGS) $<.s -o $@
	$(RM) $<.s

clean:
	$(RM) *.elf *.o *.bin

.PHONY: hack help clean

# Common portable makefile things

ARCH_MCPU?=cortex-a5

ARCH_RUST_TARGET?=armv7-unknown-linux-gnueabi

ARCH_LD_LIBS?=-lc -lgcc -lm

ARMCC?=arm-none-eabi
RUSTC?=rustc
ARMCFLAGS?=-c -mcpu=$(ARCH_MCPU) -Idrivers/$(ARCH)/ -I. -Isrc/ -g -Wall -O2

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@
%.o: %.s $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# output rule for rust files
RARCH=$(ARCH_RUST_TARGET)
RFLAGS=-C opt-level=2 --target $(RARCH) --emit obj --crate-type rlib
%.o: %.rs $(EXTERN_DEPS) $(wildcard *.rs)
	$(RUSTC) $(RFLAGS) $< -o $@	

clean:
	$(RM) $(TOPL)/src/*.o $(TOPL)/drivers/emu/*.o *.o *.elf *.bin *.out $(TOPL)/dump
	cd tool && $(MAKE) clean
	cd emulator && $(MAKE) clean

build-tool:
	cd tool && $(MAKE)

build-emu:
	cd emulator && $(MAKE)

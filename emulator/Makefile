-include ../config.mak

# Installation:
# pip3 install unicorn

model?=xf1_101
dump?=/home/daniel/Downloads/dump_0x00e_32mb.bin

ARMCC=arm-none-eabi
ARMCFLAGS=-c -include ../model/$(model).h -I../src/

ARMCFLAGS+=-fpic -mcpu=cortex-a7

ARMLDFLAGS=-nostdlib -nostartfiles -T Linker.ld

all: test.bin $(dump)
	python3 main.py $(dump)

# Recompile when these files are changed
BUILD_DEPS=../model/stub.h ../model/$(model).h main.py Makefile Linker.ld

test.bin: $(BUILD_DEPS) main.o stub.o
	$(ARMCC)-ld main.o stub.o $(ARMLDFLAGS) -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.bin

%.o: %.c $(BUILD_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# Solely for compiling in stubs
stub.o: $(BUILD_DEPS) stub.S
	$(ARMCC)-gcc -D FPIC -D STUBS $(ARMCFLAGS) stub.S -o stub.o

$(dump):
	cd ..; $(MAKE) lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT

clean:
	$(RM) *.o *.elf *.bin

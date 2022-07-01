-include ../config.mak

# Installation:
# pip3 install unicorn

model?=xf1
dump?=/home/daniel/Downloads/dump_0x00e_32mb.bin

ARMCC=arm-none-eabi
ARMCFLAGS=-c -include ../model/$(model).h -I../src/

ARMCFLAGS+=-fpic

all: test.o $(dump)
	python3 main.py $(dump)

# Recompile when these files are changed
BUILD_DEPS=../model/stub.h ../model/$(model).h main.py Makefile

test.o: $(BUILD_DEPS) test.c stub.o
	$(ARMCC)-gcc $(ARMCFLAGS) test.c -o test.o
	$(ARMCC)-ld test.o stub.o -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.o

# Solely for compiling in stubs
stub.o: $(BUILD_DEPS)
	touch stub.S
	$(ARMCC)-gcc -D FPIC -D STUBS $(ARMCFLAGS) stub.S -o stub.o
	$(RM) stub.S

$(dump):
	cd ..; $(MAKE) lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT

clean:
	$(RM) *.o *.elf stub.S

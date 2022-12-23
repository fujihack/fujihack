all: test.bin $(dump)
	python3 main.py $(dump)

TOPL=..
-include ../config.mak
include ../Makefile

# Installation:
# pip3 install unicorn

dump?=~/Documents/dump/RAM.BIN

ARMCFLAGS=-c -g -include ../model/$(model).h -I../src/
ARMCFLAGS+=-fpic -mcpu=cortex-a7
ARMLDFLAGS=-nostdlib -nostartfiles -T ../src/Linker.ld

# Recompile when these files are changed
BUILD_DEPS=../model/stub.h ../model/$(model).h main.py Makefile ../src/Linker.ld ../patch/*
O_FILES=entry.o main.o stub.o rust.o

test.bin: $(BUILD_DEPS) $(O_FILES)
	$(ARMCC)-ld $(O_FILES) $(ARMLDFLAGS) -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.bin

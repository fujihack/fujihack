# Installation:
# pip3 install unicorn

model?=xf1
dump?=/home/daniel/Downloads/dump_0x00e_32mb.bin

ARMCC=arm-none-eabi
ARMCFLAGS=-c -include ../model/$(model).h -I../src/

#ARMCFLAGS+=-fpic -mpic-register=r9 -msingle-pic-base
ARMCFLAGS+=-mlong-calls

all: test.o $(dump)
	python3 main.py $(dump)

BUILD_DEPS=../model/$(model).h main.py Makefile link.ld

test.o: $(BUILD_DEPS) test.c stub.o
	$(ARMCC)-gcc $(ARMCFLAGS) test.c -o test.o
	$(ARMCC)-ld -Ttext=$(shell stat -L -c %s $(dump)) test.o stub.o -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.o

# Solely for compiling in stubs
stub.o:
	touch stub.S
	$(ARMCC)-gcc -DSTUBS $(ARMCFLAGS) stub.S -o stub.o
	$(RM) stub.S

$(dump):
	cd ..; make lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT

clean:
	$(RM) *.o *.elf stub.S

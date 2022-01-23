# Doesn't have compressed firmware
model?=hs20exr

ARMCC=arm-none-eabi
CFLAGS=-c -include ../model/$(model).h

dump?=/home/daniel/Desktop/fujifilm-backup/dump/dump_xf1_0x0

all: Makefile unicorn-arm.min.js test.o
	node main.js

test.o: test.c stub.o
	$(ARMCC)-gcc test.c $(CFLAGS) -o test.o
	$(ARMCC)-ld -Bstatic test.o -Ttext 0x20f10e8 -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.o

stub.o:
	touch stub.S
	$(ARMCC)-gcc -D STUBS $(CFLAGS) stub.S -o stub.o

unicorn-arm.min.js:
	curl -L -O https://github.com/AlexAltea/unicorn.js/releases/download/v1.0/unicorn-arm.min.js

clean:
	$(RM) *.o *.elf

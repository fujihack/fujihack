# Installation:
# pip3 install unicorn

model?=xf1
dump?=/home/daniel/Desktop/fujifilm-backup/dump/dump_xf1_0x0

ARMCC=arm-none-eabi
ARMCFLAGS=-c -include ../model/$(model).h -I../src/

all: test.o $(dump)
	python3 main.py $(dump)

test.o: test.c stub.o
	$(ARMCC)-gcc $(ARMCFLAGS) test.c -o test.o
	$(ARMCC)-ld -Bstatic test.o stub.o -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.o

# Solely for compiling in stubs
stub.o:
	touch stub.S
	$(ARMCC)-gcc -DSTUB $(ARMCFLAGS) stub.S -o stub.o
	$(RM) stub.S

$(dump):
	cd ..; make lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT

clean:
	$(RM) *.o *.elf stub.S

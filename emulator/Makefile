# Doesn't have compressed firmware
model?=hs20exr

ARMCC=arm-none-eabi

all: test.o ../output
	python3 main.py

test.o: test.c
	$(ARMCC)-gcc -c -include ../model/$(model).h test.c -o test.o
	$(ARMCC)-ld -Bstatic test.o -o test.elf
	$(ARMCC)-objcopy -O binary test.elf test.o

../output:
	cd ..; make lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT

clean:
	$(RM) *.o *.elf

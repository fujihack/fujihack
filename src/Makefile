MODEL?=xf1

CC:=arm-none-eabi-
CFLAG:=-include ../model/${MODEL}.h

all:
	${CC}gcc ${CFLAG} -nostdlib -c -o lib.o lib.c
	${CC}gcc ${CFLAG} -nostdlib -c -o testc.o test.c
	${CC}gcc ${CFLAG} -nostdlib -c -o test.o test.S
	${CC}ld -Bstatic test.o testc.o lib.o -Ttext 0x00e572e8 -o test.elf
	${CC}objcopy -O binary test.elf test.o

	python3 main.py

clean:
	rm *.elf *.o

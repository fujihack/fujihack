MODEL?=xf1

CC:=arm-none-eabi-
CFLAG:=-include ../model/${MODEL}.h -nostdlib -c

all: compile hack

compile:
	${CC}gcc ${CFLAG} lib.c -o lib.o
	${CC}gcc ${CFLAG} test.c -o testc.o

	${CC}gcc -D STUBS ${CFLAG} -o test.o test.S
	
	${CC}ld -Bstatic *.o -Ttext 0x00e572e8 -o test.elf
	${CC}objcopy -O binary test.elf test.o
	ls -l test.o

hack:
	python3 main.py

clean:
	rm *.elf *.o

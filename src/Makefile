MODEL?=xf1

# Tell linker code is at some address
ADDR=0x00e572e8

# These are set in order for the linker
FILES=entry.o test.o lib.o stub.o

CC=arm-none-eabi-
CFLAG=-include ../model/$(MODEL).h -nostdlib -c
LDFLAGS=-Bstatic $(FILES) -Ttext $(ADDR)

all: main.o

# output rule for C files
%.o: %.c
	$(CC)gcc $(CFLAG) $< -o $@

# output rule for assembly files
%.o: %.S
	$(CC)gcc $(CFLAG) $< -o $@

# only stub.S is compiled with stubs
stub.o: stub.S
	$(CC)gcc -D STUBS $(CFLAG) $< -o $@

main.o: $(FILES)
	$(CC)ld $(LDFLAGS) -o main.elf
	$(CC)objcopy -O binary main.elf main.o
	@ls -l main.o

hack: main.o
	python3 main.py

clean:
	rm -rf *.elf *.o

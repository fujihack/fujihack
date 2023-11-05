-include config.mak

# Compile Unicorn VM engine and pull cnlohr rawdraw
UNICORN?=/home/$(USER)/Pulled/unicorn
RAWDRAW?=/home/$(USER)/Pulled/rawdraw

FILES=main.o emulator.o bmp.o

all: emu.o

$(UNICORN):
	echo Clone and install unicorn VM in $(UNICORN) or modify UNICORN in config.mak
$(RAWDRAW):
	echo Clone rawdraw in $(RAWDRAW) or modify RAWDRAW in config.mak

CFLAGS?=-I$(RAWDRAW) -I../drivers/emu/ -I. -Wall -g

emu.o: $(FILES) Makefile $(UNICORN) $(RAWDRAW)
	$(CC) $(FILES) -lunicorn -lX11 -lGL -lm -o emu.o

clean:
	$(RM) *.o *.elf

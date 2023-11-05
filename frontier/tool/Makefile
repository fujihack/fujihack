-include config.mak

# Compile Unicorn VM engine and pull cnlohr rawdraw
UNICORN?=/home/$(USER)/Pulled/unicorn
RAWDRAW?=/home/$(USER)/Pulled/rawdraw

FILES=main.o pack.o

all: frontier.o

CFLAGS?=-I$(RAWDRAW) -I../drivers/emu/ -I. -Wall -g

frontier.o: $(FILES) Makefile
	$(CC) $(FILES) -o frontier.o

install: frontier.o
	cp frontier.o /bin/frontier

clean:
	$(RM) *.o *.elf

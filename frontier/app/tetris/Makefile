TOPL?=../../
NAME=tetris
all: $(NAME).elf
include $(TOPL)/common.mk

ARMCFLAGS=-c -I$(TOPL)/src/ -O2 -g -fno-builtin -mcpu=cortex-a5
FILES=main.o

main.o: ptetris.h

$(NAME).elf: $(FILES)
	$(ARMCC)-ld -r $(FILES) -o $(NAME).elf


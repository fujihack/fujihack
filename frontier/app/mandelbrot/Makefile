NAME=mandelbrot
all: $(NAME).elf
TOPL?=../../
include $(TOPL)/common.mk

ARMCFLAGS=-c -I$(TOPL)/src/ -O4 -mcpu=cortex-a7
FILES=mandelbrot.o

$(NAME).elf: $(FILES)
	$(ARMCC)-ld -r $(FILES) -o $(NAME).elf

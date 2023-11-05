NAME=bible
all: $(NAME).elf
TOPL?=../../
include $(TOPL)/common.mak

ARMCFLAGS=-c -I$(TOPL)/src/ -O4 -mcpu=cortex-a7
FILES=main.o biblec.o

$(NAME).elf: $(FILES)
	$(ARMCC)-ld -r $(FILES) -o $(NAME).elf

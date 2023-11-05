NAME=hello
all: $(NAME).elf
TOPL?=../../
include $(TOPL)/common.mak

ARMCFLAGS=-c -I$(TOPL)/src/ -mcpu=cortex-a5 -mabi=aapcs
FILES=main.o

$(NAME).elf: $(FILES)
	$(ARMCC)-ld -r $(FILES) -o $(NAME).elf

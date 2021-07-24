# A better build system will eventually
# be written.

# Default firm.c target
t ?= unpack

# Customize firm.c flags here:
OUTPUT_FILE ?= "/media/daniel/disk/FPUPDATE.DAT"
TEMP_FILE ?= "output"
INPUT_FILE ?= "/home/daniel/Documents/fujifilm/hs20exr.DAT"
ASM_FILE ?= "dump.o"
START_ADDR ?= 0x0040679c

FFLAG := -D ARGS
FFLAG += -D OUTPUT_FILE='${OUTPUT_FILE}'
FFLAG += -D TEMP_FILE='${TEMP_FILE}'
FFLAG += -D INPUT_FILE='${INPUT_FILE}'
FFLAG += -D ASM_FILE='${ASM_FILE}'
FFLAG += -D START_ADDR=${START_ADDR}

CC = tcc

ASMFLAGS := -c -marm
ARM := arm-none-eabi

all:
	@rm -rf ${OUTPUT_FILE}
	@touch ${OUTPUT_FILE} ${TEMP_FILE}

	@${CC} firm.c -o firm.o
	@./firm.o ${t}

	@rm firm.o

# Quick messy diff
diff:
	@xxd FPUPDATE.DAT > a
	@xxd ${f} > b
	-@diff a b
	@rm -rf a b

clean:
	@rm -rf a b *.out *.o ${OUTPUT_FILE} *.elf *.o ${TEMP_FILE}

# Lay out memory
lay:
	@make t=unpack
	@${CC} lay.c
	@./a.out

# Assemble dump.S into dump.o
asm:
	@${ARM}-gcc ${ASMFLAGS} ${INCLUDE} -o dump.o dump.S
	@${ARM}-ld -Bstatic dump.o -Ttext 0 -o dump.elf
	@${ARM}-objcopy -O binary dump.elf dump.o
	@hexdump -C dump.o

	@make t=unpack
	@make t=pack
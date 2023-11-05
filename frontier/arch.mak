# Specifies data for each device
ifeq ($(ARCH),emu)
ARCH_FILES=$(patsubst %, drivers/emu/%, mem.o sys.o bmp.o io.o)
ARCH_MCPU=cortex-a5
ARCH_RUST_TARGET=armv7-unknown-linux-gnueabi
ARCH_LD_SCRIPT=Linker.ld
ARCH_BOOT_FILE=drivers/emu/boot.o
endif

ifeq ($(ARCH),qemu)
ARCH_FILES=$(patsubst %, drivers/qemu/%, minimal.o uart.o)
ARCH_MCPU=arm926ej-s
ARCH_RUST_TARGET=armv7-unknown-linux-gnueabi

FILES=drivers/qemu/boot.o $(ARCH_FILES)

ARCH_LD_SCRIPT=drivers/qemu/Linker.ld
ARCH_LD_LIBS=
endif

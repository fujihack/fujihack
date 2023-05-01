TOPL=../..
-include $(TOPL)/config.mak
include $(TOPL)/Makefile

ARMCFLAGS=-fpic -mcpu=cortex-a5 -include $(TOPL)/model/$(model).h -c -I $(TOPL)/src/
HACK_BIN_DEPS=test.o

hack.bin: $(HACK_BIN_DEPS)
	$(ARMCC)-ld $(ARMLDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

	cp hack.bin /media/daniel/3832-3561/ffboot.bin
	cp hack.bin /media/daniel/3832-3561/ffsys.bin
	cp hack.bin /media/daniel/3832-3561/ffuser.bin
	umount /media/daniel/3832-3561/

# XF1 voice memo multi injection config.mak

all: help

model=xf1_101
output=FPUPDATE.DAT
temp_file=output

$(call importMacro, model/$(model).h, FIRMWARE_MEMO, %x, FIRMWARE_MEMO)
$(call importMacro, model/$(model).h, FIRM_DUMP_ADDR, %x, FIRM_DUMP_ADDR)

FIRMWARE_INJECT_MAX=300
MEM_INJECT_ADDR=0

multi_inject:
	$(MAKE) clean-out
	$(MAKE) unpack
	$(MAKE) inject input=$(input) FIRMWARE_INJECT_ADDR=$(FIRM_DUMP_ADDR) asm_file=patch/main.S
	$(MAKE) clean-out
	$(MAKE) inject input=$(input) FIRMWARE_INJECT_ADDR=$(FIRMWARE_MEMO) asm_file=patch/jump.S
	$(MAKE) pack

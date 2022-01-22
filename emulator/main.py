from unicorn import *
from unicorn.arm_const import *
import sys

MAX_MEM = 50 * 1024000
BASE_ADDR = 0x0

def printRegs(e, length):
    print("[I]   At PC:", hex(e.reg_read(UC_ARM_REG_PC)))
    print("[I]   In injection:", hex(e.reg_read(UC_ARM_REG_PC) - length - 0x013fddcc))
    print("[I]   LR:", hex(e.reg_read(UC_ARM_REG_LR)))
    print("[I]   R0:", hex(e.reg_read(UC_ARM_REG_R0)), "/", e.reg_read(UC_ARM_REG_R0))

def start():
    e = Uc(UC_ARCH_ARM, UC_MODE_ARM)

    print("[I] Loading code...")
    fp = open(sys.argv[1], "rb")
    firmware = fp.read()
    print("[I] Firmware is", len(firmware), "bytes")

    print("[I] Allocating " + str(MAX_MEM / 1000 / 1000) + "mb memory...")
    e.mem_map(BASE_ADDR, MAX_MEM, UC_PROT_ALL)
    e.mem_write(BASE_ADDR, firmware)
    
    # Write test.o right after firmware
    fp = open("test.o", "rb")
    injection = fp.read()
    e.mem_write(BASE_ADDR + len(firmware), injection)
    print("[I] Injection is", len(injection), "bytes")
    
    # Give the code some stack space
    e.reg_write(UC_ARM_REG_SP, len(firmware) + len(injection));

    start = BASE_ADDR + len(firmware)
    end = BASE_ADDR + len(firmware) + len(injection) - 4

    # Function returns to end
    e.reg_write(UC_ARM_REG_LR, end);

    print("[I] Starting emulator...")
    try:
        e.emu_start(start, end, 0, 0)
    except UcError as err:
        print("[-] Unicorn error:", err)
        printRegs(e, len(firmware))
        exit()

    print("[+] Success.")
    printRegs(e, len(firmware))


start()

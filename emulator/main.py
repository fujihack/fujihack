from unicorn import *
from unicorn.arm_const import *
import sys, multiprocessing

MAX_MEM = 0x10000000

# Base addr of firmware, injected code should be
# position independent
BASE_ADDR = 0x0

def sanitizeString(e, addr):
    final = ""

    data = e.mem_read(addr, 100)
    for b in data:
        if b == 0:
            break
        elif b < 128:
            final += chr(b)
    return final

def printRegs(e, length):
    r0 = e.reg_read(UC_ARM_REG_R0)
    pc = e.reg_read(UC_ARM_REG_PC)
    lr = e.reg_read(UC_ARM_REG_LR)

    print("[I]   At PC:", hex(pc), "/", pc)
    print("[I]   In injection:", hex(pc - length), " inst #" + str((pc - length) / 4))
    print("[I]   LR:", hex(lr))
    print("[I]   R0:", hex(r0), "/", r0)
    print("[I]   R9:", hex(e.reg_read(UC_ARM_REG_R9)))
    print("[I]   Return String: '" + sanitizeString(e, r0) + "'")

'''
    tmp = e.mem_read(0x20f10e8+0x418, 4)
    for i in reversed(tmp):
        print("%x" %i, end="")
    print("")
'''

def runEmu(e, start, end, firmware):
    try:
        e.emu_start(start, end, 0, 0)
    except UcError as err:
        print("[-] Unicorn error:", err)
        printRegs(e, len(firmware))
        return
    print("[+] Success.")
    printRegs(e, len(firmware))

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
    fp = open("test.bin", "rb")
    injection = fp.read()
    e.mem_write(BASE_ADDR + len(firmware), injection)
    print("[I] Injection is", len(injection), "bytes")
    
    # Give the code some stack space, space it
    # away from code to limit interference
    e.reg_write(UC_ARM_REG_SP, len(firmware) + len(injection) + 128);
    e.reg_write(UC_ARM_REG_SB, 1);

    start = BASE_ADDR + len(firmware)
    end = BASE_ADDR + len(firmware) + len(injection)

    # Function returns to end
    e.reg_write(UC_ARM_REG_LR, end);

    print("[I] Starting emulator on new thread...")
    print("[I] Starting at", hex(start))
    p = multiprocessing.Process(target = runEmu,
        args = (e, start, end, firmware))
    p.start()
    p.join(1)
    if p.is_alive():
        print("[-] Thread timeout! Killing...")
        p.kill()
        return 1
    return 0

sys.exit(start())

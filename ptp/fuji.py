# Reverse engineered Fujifilm vendor specifc PTP commands

import ptpy
from random import randrange

import hijack
hijack.setup()

FUJI_CREATE_FILE = 0x900c
FUJI_UNKNOWN1 = 0x900d
FUJI_WRITE_FILE = 0x901d

FUJI_FPUPDATE = 0xb802
FUJI_AUTO_ACT = 0x3002

def packFile(fileCode):
    string = 0
    if fileCode == FUJI_FPUPDATE:
        string = "FPUPDATE.DAT"
    elif fileCode == FUJI_AUTO_ACT:
        string = "AUTO_ACT.SCR"

    # Convert string to 16 bit wide (Windows style)
    byte = bytearray(0)
    for i in string:
        byte += str(i).encode()
        byte += bytearray(1)
    byte += bytearray(2)

    # Prepare Data struct
    header = bytes([0, 0, 0, 0])
    header += (fileCode).to_bytes(4, 'little')
    header += bytes([0x34, 0x84, 0xa1, 0x1]) # magic numbers

    # 40 characters of blank Space, then Windows style \r character
    header += bytearray(40) + b'\r'
    
    payload = header + byte

    return payload

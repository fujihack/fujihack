# Reverse engineered Fujifilm vendor specifc PTP commands

import ptpy
from random import randrange

import hijack
hijack.setup()

FUJI_CREATE_FILE = 0x900c # same as 0x100c?
FUJI_UNKNOWN1 = 0x900d # same as 0x100d?
FUJI_WRITE_FILE = 0x901d

# These are PTP standard ancillary format codes
FUJI_FOLDER   = 0x3800
FUJI_FPUPDATE = 0xb802
FUJI_AUTO_ACT = 0x3002
FUJI_DSCF_JPG = 0x3801
FUJI_DSCF_RAF = 0xb103
FUJI_XXXXXXXX = 0xb003 # ?
FUJI_XXXXXXX2 = 0x3001 # ?
FUJI_XXXXXXX3 = 0x3808 # ?

def packFile(fileCode, string=None, size=0x989680, storage_id=0x10000001):
    if string == None:
        if fileCode == FUJI_FPUPDATE:
            string = "FPUPDATE.DAT"
        elif fileCode == FUJI_AUTO_ACT:
            string = "AUTO_ACT.SCR"
        elif fileCode == FUJI_DSCF_JPG:
            string = "DSCF0000.JPG"

    # Convert string to 16 bit wide (Windows style)
    byte = bytearray(0)
    for i in string:
        byte += str(i).encode()
        byte += bytearray(1)
    byte += bytearray(2)

    # Prepare Data struct
    header = (storage_id).to_bytes(4, "little")
    header += (fileCode).to_bytes(4, "little")
    header += (size).to_bytes(4, "little") # magic numbers

    # 40 characters of blank Space, then carriage return
    header += bytearray(40) + bytes([13])
    
    payload = header + byte

    return payload

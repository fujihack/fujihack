# Reverse engineered Fujifilm vendor specifc PTP commands

import ptpy
from random import randrange

import hijack
hijack.setup()

FUJI_CREATE_FILE = 0x900c
FUJI_UNKNOWN1 = 0x900d
FUJI_WRITE_FILE = 0x901d

FUJI_UNKNOWN2 = 0x9801 # InvalidObjectFormatCode
FUJI_UNKNOWN3 = 0x9802 # Invalid_ObjectPropCode, NO DATA
FUJI_UNKNOWN4 = 0x9803 # InvalidObjectHandle
FUJI_UNKNOWN5 = 0x9805 # Specification_By_Group_Unsupported

FUJI_FPUPDATE = 0xb802
FUJI_AUTO_ACT = 0x3002
FUJI_DSCF_JPG = 0x3801
FUJI_DSCF_RAF = 0xb103
FUJI_XXXXXXXX = 0xb003 # ?
FUJI_XXXXXXX2 = 0x3001 # ?
FUJI_XXXXXXX3 = 0x3808 # ?

def packFile(fileCode):
    string = 0
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
    header = bytes([0, 0, 0, 0])
    header += (fileCode).to_bytes(4, 'little')
    header += bytes([0xff, 0xff, 0xff, 0xff]) # magic numbers
    #header += bytes([0x34, 0x84, 0xa1, 0x1]) # magic numbers

    # 40 characters of blank Space, then carriage return
    header += bytearray(40) + bytes([13])
    
    payload = header + byte

    return payload

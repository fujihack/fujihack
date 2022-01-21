#!/usr/bin/env python
import ptpy
from random import randrange

FUJI_CREATE_FILE = 0x900c
FUJI_UNKNOWN1 = 0x900d
FUJI_WRITE_FILE = 0x901d

FUJI_FPUPDATE = 0xb802
FUJI_AUTO_ACT = 0x3002

# SendObjectInfo

# 36876 / 0x900c / Create file
# 36877 / 0x900d / ???
# 36893 / 0x901d / Write to file

camera = ptpy.PTPy()

with camera.session():
    string = "FPUPDATE.DAT"

    # Convert 8 bit string to 16 bit
    byte = bytearray(0)
    for i in string:
        byte += str(i).encode()
        byte += bytearray(1)
    byte += bytearray(2)

    # Prepare (struct?)
    header = bytes([0, 0, 0, 0])
    header += (FUJI_FPUPDATE).to_bytes(4, 'little')
    header += (0x2048590).to_bytes(4, 'little') # ???
    header += bytes([0, 0, 0, 0])
    header += bytes([0, 0, 0, 0])

    header += bytearray(0x20) + b'\r'
    
    payload = header + byte

    # Both don't seem to do anything
    print(camera.custom_send(FUJI_CREATE_FILE, [], payload))
    print(camera.custom_send(FUJI_WRITE_FILE, [], bytes([1, 2, 3, 4, 5, 6, 7, 8, 9])))

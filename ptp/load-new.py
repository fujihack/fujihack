# Load code into firmware patch
import sys
import ptpy
import ctypes
from random import randrange

import hijack
hijack.setup()

# See main.S
HIJACK = 0x9805

ZERO = 4
WRITE = 5
EXEC = 6
RESET = 7
SETADDR = 8
GET = 9

camera = ptpy.PTPy()

with camera.session():
    print("sending...")
    
    print(camera.custom_recv(HIJACK, [SETADDR, 0x00e5e228]))
    print(camera.custom_recv(HIJACK, [RESET]))
    print(camera.custom_recv(HIJACK, [WRITE, 66]))
    print(camera.custom_recv(HIJACK, [ZERO]))
    
    print("recieved")
    print(camera.get_device_info().VendorExtensionDesc)

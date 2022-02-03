import ptpy
import ctypes
from random import randrange

import hijack
hijack.setup()

# See main.S
HIJACK = "GetThumb"
ZERO = 8
RESET = 7
EXEC = 6
WRITE = 5

f = open("hack.bin", "rb")
c = f.read()

camera = ptpy.PTPy()

with camera.session():
    camera.custom_recv(HIJACK, [RESET])

    for i in c:
        if i == 0:
            print("Sending ZERO")
            camera.custom_recv(HIJACK, [ZERO, 255])
        else:
            print("Sending", hex(i))
            camera.custom_recv(HIJACK, [WRITE, i])

    print("Executing...")
    camera.custom_recv(HIJACK, [EXEC])

    print(camera.get_device_info().VendorExtensionDesc)

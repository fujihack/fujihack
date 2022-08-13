# Run code without loading
import ptpy
import ctypes
from random import randrange

import hijack
hijack.setup()

# See main.S
HIJACK = "GetThumb"
RESET = 7
EXEC = 6
WRITE = 5

camera = ptpy.PTPy()

with camera.session():
    camera.custom_recv(HIJACK, [RESET])

    print("Executing...")
    camera.custom_recv(HIJACK, [EXEC])

    print(camera.get_device_info().VendorExtensionDesc)

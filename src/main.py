import ptpy
from random import randrange
import ctypes

camera = ptpy.PTPy()

f = open("main.o", "rb")
c = f.read()

with camera.session():
    camera.custom2(0x100a, [7])
    for i in c:
        if i == 0:
            print("Sending 8")
            camera.custom2(0x100a, [8, 255])
        else:
            print("Sending", hex(i))
            camera.custom2(0x100a, [5, i])
    print("Executing...")
    camera.custom2(0x100a, [6])
    print(camera.get_device_info().VendorExtensionDesc)

    '''
    a = camera.get_device_infob()
    f2 = open("dump", "wb")
    f2.write(a.Data)
    f2.close()
    '''

import ptpy
from random import randrange
import ctypes

camera = ptpy.PTPy()

f = open("test.o", "rb")
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

    f2 = open("dump", "wb")
    counter = 0

    while True:
        camera.custom2(0x100a, [6])
    
        a = camera.get_device_infob().Data
        i2 = 9
        for i in range(20):
            f2.write( (a[i2]).to_bytes(1, "little") )
            i2 += 2

        f2.flush()
        print(counter)
        counter += 20

    f2.close()

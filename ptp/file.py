# Basic File test
import ptpy, sys
from random import randrange

import hijack
from fuji import *

camera = ptpy.PTPy()

with camera.session():
    #print(camera.custom_send(FUJI_CREATE_FILE, packFile(FUJI_AUTO_ACT), param=[])) # novalidobjinfo
    print(camera.custom_send(0x9805, bytes(), param=[1, 1, 1]))
    #print(camera.custom_send(FUJI_CREATE_FILE, packFile(FUJI_AUTO_ACT)))
    #print(camera.custom_send(FUJI_WRITE_FILE, bytes(1000)))


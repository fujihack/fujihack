# Basic File test
import ptpy, sys
from random import randrange

import hijack
from fuji import *

camera = ptpy.PTPy()

with camera.session():
    print(camera.custom_send(FUJI_CREATE_FILE, packFile(FUJI_AUTO_ACT), param=[]))
    #print(camera.custom_send(FUJI_WRITE_FILE, bytes(10000)))
    #print(camera.custom_send(FUJI_UNKNOWN3, bytes(), param=[13, 132, 111, 1, 1]))
    #print(camera.custom_send(FUJI_CREATE_FILE, packFile(FUJI_AUTO_ACT)))
    #print(camera.custom_send(FUJI_WRITE_FILE, bytes(1000)))


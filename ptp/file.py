# Basic File test
import ptpy, sys
from random import randrange

import hijack
from fuji import *

camera = ptpy.PTPy()

with camera.session():
    print(camera.custom_send(0x9802, bytes(), param=[123])) # novalidobjinfo
    #print(camera.custom_send(FUJI_CREATE_FILE, packFile(FUJI_AUTO_ACT)))
    #print(camera.custom_send(FUJI_WRITE_FILE, bytes(1000)))


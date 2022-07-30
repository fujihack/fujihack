# Basic interfacing
import ptpy, sys
from random import randrange

import hijack
from fuji import *

camera = ptpy.PTPy()

with camera.session():
    print(camera.custom_send(FUJI_CREATE_FILE, packFile(0x3800, string = "C:\\tests")))
    print(camera.custom_send(FUJI_WRITE_FILE, bytes()))

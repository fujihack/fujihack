# Load code into firmware patch
import sys
import ptpy
import ctypes
from random import randrange

import hijack
hijack.setup()

# What command has been hijacked
HIJACK = 0x9805

# Options for PTP hack
ZERO = 4
WRITE = 5
EXEC = 6
RESET = 7
SETADDR = 8
GET = 9

def runCode(file):
    global ZERO, WRITE, EXEC, RESET, SETADDR, GET
    f = open(file, "rb")
    c = f.read()
    
    camera = ptpy.PTPy()

    with camera.session():
        camera.custom_recv(HIJACK, [RESET])
        percent = 0
        byte = 0
        for i in c:
            if i == 0:
                camera.custom_recv(HIJACK, [ZERO, 255])
            else:
                camera.custom_recv(HIJACK, [WRITE, i])
            percent = (byte / len(c)) * 100
            byte += 1
            if (percent % 10) == 0:
                print(str(percent) + "%")
        run(camera)

def run(camera = None):
    if camera == None:
        camera = ptpy.PTPy()
    print("Executing...")
    camera.custom_recv(HIJACK, [EXEC])
    print(camera.get_device_info().VendorExtensionDesc)

def dumpRam(file):
    global ZERO, WRITE, EXEC, RESET, SETADDR, GET
    f = open(file, "wb")
    
    camera = ptpy.PTPy()
    
    with camera.session():
        camera.custom_recv(HIJACK, [RESET])

        # Dump 64 mb
        for i in range(64000000):
            if (i % 10000) == 0:
                print("Read", i, "bytes")
            x = camera.custom_recv(HIJACK, [GET])
            #x.write(bytesarray(x......))

def parseCli():
    for i in range(len(sys.argv)):
        c = sys.argv[i]
        if c[0] == '-' and len(c) == 2:
            if c[1] == 'o':
                # Hijack the 'GetThumb' command for the old hack
                HIJACK = 0x100a
                return
            elif c[1] == 'l':
                runCode(sys.argv[i + 1])
                return
            elif c[1] == 'd':
                dumpRam(sys.argv[i + 1])
                return
            elif c[1] == 'r':
                run()
                return
parseCli()

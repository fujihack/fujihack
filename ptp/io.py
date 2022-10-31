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

f = open("io5.bin", "wb")
addr = 0xfe800000

camera = ptpy.PTPy()
with camera.session():
	while True:
		x = camera.custom_recv(HIJACK, [GET, addr])
		print(x.Parameter[0])
		f.write(x.Parameter[0].to_bytes(4, "little"))
		f.flush()

		addr += 4

f.close()

import ptpy, sys
from random import randrange

import hijack
from fuji import *

# PTPy seems to handle large packets fine
# The PTP spec says the max size is 512 bytes but
# somehow 50k works fine??
PACKET_DATA_SIZE = 50000

camera = ptpy.PTPy()

with camera.session():
    file = open(sys.argv[1], "rb")
    if file == "":
        print("Invalid file")
        sys.exit(1)
    
    print("Reading file into variable")
    data = file.read()
    
    # Initialize FPUPDATE.DAT
    camera.custom_send(FUJI_CREATE_FILE, packFile(FUJI_FPUPDATE))

    # Write some test bytes
    percent = 0
    pos = 0
    while pos <= len(data):
        camera.custom_send(FUJI_WRITE_FILE, data[pos:pos + PACKET_DATA_SIZE])
        pos += PACKET_DATA_SIZE

        newPercent = round((pos / len(data)) * 100)
        if newPercent > percent:
            print(str(newPercent) + "%")
        percent = newPercent

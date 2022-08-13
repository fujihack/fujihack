# Stock PTP, upload files via vendor commands
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

    code = FUJI_FOLDER
    if sys.argv[1].endswith(".DAT"):
        code = FUJI_FPUPDATE
    elif sys.argv[1].endswith(".SCR"):
        code = FUJI_AUTO_ACT
    
    # Initialize FPUPDATE.DAT
    r = camera.custom_send(FUJI_CREATE_FILE, packFile(code))
    if r.ResponseCode != "OK":
        print("Error:", r)
        sys.exit(1);

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

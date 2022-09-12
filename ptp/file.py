# Basic interfacing tests
import ptpy, sys
from random import randrange

import hijack
from fuji import *

camera = ptpy.PTPy()

with camera.session():
    sid = camera.get_storage_ids()[0]
    print(sid, camera.get_storage_info(sid))
    print(camera.get_object_handles(sid, in_root=True))

    print(camera.custom_send(FUJI_CREATE_FILE, packFile(0x3800, string="FOO", size=4, storage_id=sid)))
    print(camera.custom_send(FUJI_WRITE_FILE, bytes([0xa, 0xa, 0xa, 0xa])))


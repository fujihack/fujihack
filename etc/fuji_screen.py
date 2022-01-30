from tkinter import *
import math
w = Tk()
w.title("Fuji Emulator")

wid = 640
hei = 480

fp = open("/home/daniel/Desktop/fujifilm-backup/dump/dump_xf1_0x0", "rb")
b = 0

c = Canvas(w, width = wid, height = hei)
c.pack()

def draw():
    i = 0
    m = 0
    while True:
        r = b[m:m + 4]
        col = "#" + ('%02x' % r[0]) + ('%02x' % r[1]) + ('%02x' % r[2])
        if i > wid:
            # Generate X/Y from i
            x = i % wid
            if x == 0:
                m += wid*4
            y = math.floor(i / wid)

            c.create_line(x, y, x + 1, y, fill=col)
        else:
            c.create_line(i, 0, i + 1, 0, fill=col)
        i += 1
        m += 4

        if m >= len(b):
            break
        if i > wid * hei:
            break

fp.seek(0x01c00000)
b = fp.read()
draw()

w.mainloop()

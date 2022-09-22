# FujiHack
FujiHack is a project that aims to reverse engineer Fujifilm cameras in order  
to achieve *interoperability*, or the ability to run custom software on the camera.

Fujifilm has used several different firmware formats and RTOSs in the past,  
and this project only works on one. Specifically, this will only work on X/GFX/HS/F/Z/Pro cameras.  
You can put your firmware file in the web patcher to see if this project supports your type.  

Check out the [FujiHack wiki](https://fujihack.github.io/) for a ton of info, and there's also a [Discord room](https://discord.gg/UZXDktvAZP).

## What's been done:
- Unpack firmware
- Repack firmware
- Modify firmware
- Harmless code execution hijacks in firmware
- Patch USB/PTP code to transfer and run custom code
- Uncovered hidden scripting abilities (see https://github.com/fujihack/fujihack/issues/13)
- Dump all sections of RAM
- Modify EEPROM
- Render text to screen
- Interface with internal SQLite
- Read IO: button status, gryoscope, accelerometer
- Limited rasterizer object rendering
- Tetris
- Primitive menus
- [Wiki](https://fujihack.github.io/)

## How to Use
**Don't, at least not yet. This is still a research project.** 
Remember that custom firmware is always dangerous, and can brick devices.  
If you want to help research, contact me.  

## Web Patcher
A [web based patcher](https://fujihack.github.io/patcher/) is in the works.  
It has the ability to unpack and export firmware file binaries. Use at your own risk.  
firm.c utility will most likely be phased out web tools are spiffier.  

## Firmware utility (firm.c)
**The plan is to phase out the firm.c utility in favor of the web patcher.**  
The Makefile will compile firm.c, as well as the assembly injection hacks.  
Type `make help` for some info.  

### Unpacking
This will simply output a bit flipped version of `input` into `temp_file`.  
```
make unpack input=~/Downloads/FPUPDATE.DAT temp_file=output
```
### Packing
Packing will bit flip `temp_file`, increment the firmware version by one,  
and copy back into `output`.

```
make pack model=xf1 temp_file=output output=FPUPDATE.DAT
```

![img](https://danielc.dev/filedump/IMG_0010.JPG)

And remember...   
**If you break it, you get to keep both pieces.**  

Copyright 2021-2022 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

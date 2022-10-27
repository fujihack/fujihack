# FujiHack
FujiHack is a project that aims to reverse engineer Fujifilm cameras in order  
to achieve *interoperability*, or the ability to run custom software on the camera.

Fujifilm has used several different firmware formats and RTOSs in the past,  
and this project only works on one. Specifically, this will only work on X/GFX/HS/F/Z/Pro cameras.  
You can put your firmware file in the web patcher to see if this project supports your type.  

Check out the [FujiHack wiki](https://fujihack.github.io/) for a ton of info, and there's also a [Discord room](https://discord.gg/UZXDktvAZP).

## What's been done:
- Unpack, repack, and modify firmware
- Harmless code execution hijacks in firmware (functionality must be replaced)
- Debugger custom firmware, with brute force searching mechanism.
- Patch USB/PTP code to transfer and run custom code, quickly debug and experiment
- Uncovered hidden scripting abilities (see https://github.com/fujihack/fujihack/issues/13)
- Dump all sections of RAM (IO regions still a mystery)
- Modify EEPROM
- Draw text to screen
- Interface with internal SQLite
- Read IO: button status, gryoscope, accelerometer
- Limited rasterizer object rendering
- Primitive live screen buffer drawing
- Task creation/suspending/closing/sleeping
- Primitive card speed tests
- Gyroscope tetris
- Primitive menus
- [Wiki](https://fujihack.github.io/)

## How to Use  
- Remember that custom firmware is always dangerous, and can brick devices.  
- If it blows up your camera, you are responsible for cleaning up the mess.

## Web Patcher
A [web based patcher](https://fujihack.github.io/patcher/) is in the works.  
It has the ability to unpack, inject, patch, and repack firmware. Use at your own risk.  
firm.c utility will be likely be phased out web tools are spiffier.  

## PTP/USB Debugger
The main firmware patch allows you to run custom code over USB, through the PTP protocol.  
This requires `arm-none-eabi-gcc`, `python3`, and `ptpy`. You can install `ptpy` with `pip3`.
```
pip3 install ptpy
```
Enter the `src/` directory. The makefile accepts a `model` argument, which can be defined by  
placing a config.mak at the top directory, or defining in CLI like so:  
```
make hack.bin model=xf1
```
That target will compile `hack.bin`, which is the bare ARM binary that is sent over by USB  
to the camera. The `hack` target can be used to compile, and then send code to the camera with a python  
script in the `ptp/` directory.

You can place custom code in `main.c`.

The makefile is set up to remove all unused variables and function in order to save space,  
the patch normally writes into a limited area in RAM.

## Rust support
fujihack has very basic Rust integration. To use it you will need rustup:
```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup target add armv5te-unknown-linux-musleabi
```

![img](https://danielc.dev/filedump/IMG_0010.JPG)

And remember...   
**If you break it, you get to keep both pieces.**  

Copyright 2021-2022 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

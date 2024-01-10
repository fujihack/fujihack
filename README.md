# Fujihack
Fujihack is a research project that aims to reverse-engineer Fujifilm cameras in order to understand and improve the firmware.

[Website](https://fujihack.org) &bull;
[Wiki](https://fujihack.github.io/) &bull;
[Discord server](https://discord.gg/UZXDktvAZP)

This codebase consists of:  
- Firmware patches to read/write/exec over USB
- CLI tool to run code and dump memory over USB
- C header files documenting Fujifilm's RTOS API
- C header files with info & RAM/firmware stubs for each camera model
- POSIX, Graphics, and I/O APIs over Fujifilm's RTOS API
- Video record limit mod, button remapping
- *Frontier*, the UI and module/scripting system
- Anything else needed to gain [interoperability](https://en.wikipedia.org/wiki/Interoperability)

## Patching firmware
- Currently, the only way to run Fujihack is with a patched firmware.
- Although the patcher has been thoroughly tested, custom firmware is *always* dangerous and can cause damage.
- There is a way to recover bricked devices (SoC boot ROM) but it hasn't been reverse-engineered yet.

A [web based patcher](https://fujihack.org/patcher/) has been written for this project. It has the ability to unpack, inject, patch, repack, and downgrade firmware. It assembles patches in browser and applies them in the firmware.

The most notable patch is the [PTP/USB debugger](https://github.com/fujihack/fujihack/blob/master/patch/debug.S), which has been ported to the XF1 and X-A2.

## PTP/USB Debugger
The debugger firmware patch adds read/write/exec abilities to the PTP code in firmware. 

Compiling it requires `arm-none-eabi-gcc` and `libusb-v1.0`.

Enter the `minimal/` directory. The makefile accepts a `model` argument, which can be defined by placing a config.mak at the top directory, or with CLI:  
```
make hack.bin model=xa2_130
```
That target will compile `hack.bin`, which is the bare ARM binary that is sent over by USB to the camera. The `hack` target can be used to compile, and then send code to the camera with the CLI utility.  

And remember...   
**If you break it, you get to keep both pieces.**  

Copyright 2021-2024 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

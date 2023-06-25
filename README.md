# FujiHack
FujiHack is a research project that aims to reverse engineer Fujifilm cameras in order to achieve stable code execution and interaction with the firmware.

[Website](https://fujihack.org) &bull;
[Wiki](https://fujihack.github.io/) &bull;
[Discord server](https://discord.gg/UZXDktvAZP)

This codebase contains the source code of the Fujihack custom menu, tweaks, and runtime, which can be loaded and used on a camera with a patched firmware.
This repo also has lots of firmware patches, experiments, and other internal info needed to gain [interoperability](https://en.wikipedia.org/wiki/Interoperability).

## Patching firmware
- Currently, the only way to run Fujihack is with a patched firmware.
- Although the patcher has been rigorously tested, custom firmware is always dangerous and can brick devices.
- There is a way to recover bricked devices (SoC boot ROM) but it hasn't been reverse engineered yet.

A [web based patcher](https://fujihack.github.io/patcher/) is provided. It has the ability to unpack, inject, patch, repack, and downgrade firmware. It assembles patches in browser and applies them in the firmware.

The most notable patch is the [PTP/USB debugger](https://github.com/fujihack/fujihack/blob/master/patch/debug.S), which has been ported to the XF1 and X-A2.

## PTP/USB Debugger
The debugger firmware patch allows you to run custom code over USB, through the PTP protocol.  

Using it requires `arm-none-eabi-gcc` and the [custom PTP CLI utility](https://github.com/fujihack/cli).

Enter the `minimal/` directory. The makefile accepts a `model` argument, which can be defined by placing a config.mak at the top directory, or defining in CLI like so:  
```
make hack.bin model=xa2_130
```
That target will compile `hack.bin`, which is the bare ARM binary that is sent over by USB to the camera. The `hack` target can be used to compile, and then send code to the camera with the CLI utility.  

And remember...   
**If you break it, you get to keep both pieces.**  

Copyright 2021-2023 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

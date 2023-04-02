# FujiHack
FujiHack is a project that aims to reverse engineer Fujifilm cameras in order  
to achieve *interoperability*, or the ability to run custom software on the camera.  

[Website](https://fujihack.org) &bull;
[Wiki](https://fujihack.github.io/) &bull;
[Discord server](https://discord.gg/UZXDktvAZP)

## How to Use  
- Remember that custom firmware is always dangerous, and can brick devices.
- The method for flashing firmware on bricked devices has not been reversed yet.

## Web Patcher
A [web based patcher](https://fujihack.github.io/patcher/) is provided.  
It has the ability to unpack, inject, patch, and repack firmware. It assembles patches in browser  
and applies them in the firmware. Generous sanity checks have been implemented, but  
custom firmware is always risky.

The most notable patch is the [PTP/USB debugger](https://github.com/fujihack/fujihack/blob/master/patch/debug.S), which has been ported to the XF1 and X-A2.

## PTP/USB Debugger
The debugger firmware patch allows you to run custom code over USB, through the PTP protocol.  


Using it requires `arm-none-eabi-gcc` and the [custom PTP CLI utility](https://github.com/fujihack/cli).

Enter the `minimal/` directory. The makefile accepts a `model` argument, which can be defined by  
placing a config.mak at the top directory, or defining in CLI like so:  
```
make hack.bin model=xa2_130
```
That target will compile `hack.bin`, which is the bare ARM binary that is sent over by USB  
to the camera. The `hack` target can be used to compile, and then send code to the camera with the CLI utility.  

And remember...   
**If you break it, you get to keep both pieces.**  

Copyright 2021-2022 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

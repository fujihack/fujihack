# FujiHack
FujiHack is a project that aims to reverse engineer Fujifilm cameras in order  
to achieve *interoperability*, or the ability to run custom software on the camera.  

[Website](https://fujihack.org) &bull;
[Wiki](https://fujihack.github.io/) &bull;
[Discord server](https://discord.gg/UZXDktvAZP)

## How to Use  
- Remember that custom firmware is always dangerous, and can brick devices.
- There is no known (yet) backup or recovery method for Fuji cameras.

## Web Patcher
A [web based patcher](https://fujihack.github.io/patcher/) is provided.  
It has the ability to unpack, inject, patch, and repack firmware. Use at your own risk.  

## PTP/USB Debugger
The main firmware patch allows you to run custom code over USB, through the PTP protocol.  
This requires `arm-none-eabi-gcc` and the [custom PTP cli utility](https://github.com/fujihack/cli).

Enter the `minimal/` directory. The makefile accepts a `model` argument, which can be defined by  
placing a config.mak at the top directory, or defining in CLI like so:  
```
make hack.bin model=xf1
```
That target will compile `hack.bin`, which is the bare ARM binary that is sent over by USB  
to the camera. The `hack` target can be used to compile, and then send code to the camera with the cli utility.  

The makefile is set up to remove all unused variables and function in order to save space,  
the patch normally writes into a limited area in RAM.

## Rust support
fujihack has very basic Rust integration. To use it you will need rustup:
```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup target add armv5te-unknown-linux-musleabi
```

And remember...   
**If you break it, you get to keep both pieces.**  

Copyright 2021-2022 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

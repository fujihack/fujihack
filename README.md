# Fujihack
Fujihack is a research project loosely based on [Magic Lantern](https://www.magiclantern.fm/) that aims to reverse-engineer Fujifilm cameras in order to understand and improve the firmware.

[Website](https://fujihack.org) &bull;
[Wiki](https://fujihack.github.io/) &bull;
[Discord server](https://discord.gg/UZXDktvAZP)

This codebase consists of:  
- Firmware patches to read/write/exec over USB
- C header files documenting Fujifilm's RTOS API
- C header files with info & RAM/firmware stubs for various camera model
- POSIX, Graphics, and I/O APIs over Fujifilm's RTOS API
- Video record limit mod, button remapping
- Anything else needed to gain [interoperability](https://en.wikipedia.org/wiki/Interoperability)

---

Copyright 2021 FujiHack by Daniel C and contributors  
FujiHack is licenced under the GNU General Public License v3.0  

# Frontier
Frontier is bare metal software that's designed to run on consumer hardware.

![PoC](https://eggnog.danielc.dev/f/74-finmvdwilqibugm0au5wi02i9g6427.png)

When finished, it will consist of:
- 32 Bit ELF loader for modules and apps
- Symbol mananger / override system
- Embedded ARM Assembler
- Runtime memory & function patching
- Scripting engine
- Basic UI & menus system (inspired by Nuklear)
- Support for buttons and touchscreens (not keyboards)
- Generic graphical ARM emulator written with Unicorn Engine
- Build tools in C to avoid GNU Make Jank

# Design
- Priority support for 32 bit ARM v6. 64 bit and Thumb is secondary, other archs will not be considered.
- Aiming for a 100k standalone ARM32 image
- Basic graphics/input API built on top of POSIX
- Apps are standard ELF objects, with an optional header including metadata (name, url, icon)
- Magic Lantern modules can also be loaded, with a basic compatibility layer
- Apps can be written in C, Rust, or JS/Lua

## Why
- I want a system I can run on my [camera](https://github.com/fujihack/fujihack), my [car](http://www.jeepproblems.com/uconnect-hack/), and anything else I want to [hack](https://hackaday.com/tag/firmware-hacking/)

# Roadmap
- [x] Basic emulator, hello world tests
- [x] Link and test libc, libm, libgcc
- [x] ELF Loader implemented
- [x] Basic UI Library
- [x] Button & mouse IO
- [ ] Multithreading in emulator
- [ ] Port to generic qemu
- [ ] Port for thumb bytecode (test on micro:bit)

# Project structure
### drivers/emu
Drivers (Kernel) for the emulator
### src/
Source code for the OS - contains loader, UI renderer, etc
### apps/
Contains all the basic test apps

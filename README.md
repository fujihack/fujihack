# Fujifilm Custom Firmware
Fujifilm firmware unpacker, repacker, and code injector.  

This will only work on modern Fujifilm cameras, such as the HS20EXR or the X-T4.  
Fujifilm has been using this firmware format since [2005](https://fujifilm-x.com/en-us/support/download/procedure-finepix-z/).  
This isn't for the Fujifilm S series. [CHDK](https://chdk.setepontos.com/index.php?topic=6484.0) already figured those out.

## Contact
- Send me an email: brikbusters@gmail.com
- Matrix: https://app.element.io/#/room/#fuji:matrix.org
- Discord: https://discord.gg/UZXDktvAZP
- Hackaday: https://hackaday.io/project/182218-fujifilm-custom-firmware

## How to Use
**Don't, at least not yet. If you are interested or have questions, contact me (See above)**

*Note: The firmware utility (firm.c) doesn't have a command line parser yet.*  
*Parameters are sent in via preprocessor definitions on compile time.*  

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

![img](https://petabyt.dev/filedump/IMG_0010.JPG)

Remember that updating to custom firmware files is  
very dangerous. I'm a Canon DSLR user. I'm just hacking  
Fujifilm cameras for fun.  

And remember...   
**If you break it, you get to keep both pieces.**  

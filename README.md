# Fujifilm Custom Firmware
Fujifilm firmware unpacker, repacker, and code injector.  

This will only work on modern Fujifilm cameras, such as the HS20EXR or the X-T4.  
Fujifilm has been using this firmware format since [2005](https://fujifilm-x.com/en-us/support/download/procedure-finepix-z/).  

## How to Use
Don't. If you want to use it, please contact me before you break anything.  
(brikbusters@gmail.com, or make an issue)  

**Unfinished** instructions for custom code executing firmware (XF-1):
```
git clone https://github.com/petabyt/fujiptp
cd fujiptp; pip3 install .; cd ..
```

```
git clone https://github.com/petabyt/fujifilm
cd fujifilm
make asm MODEL=xf1 \
  INPUT_FILE=~/Downloads/FPUPDATE.DAT \
  OUTPUT_FILE=/media/MY_CARD/FPUPDATE.DAT
```

The resulting firmware should have md5sum:  
`3f3b6cafdeaa87ae5ca084135ebb54a6`

![img](https://petabyt.dev/filedump/IMG_0010.JPG)

Remember that updating to custom firmware files is  
very dangerous. I'm a Canon DSLR user. I'm just hacking  
Fujifilm cameras for fun.  

And remember...   
**If you break it, you get to keep both pieces.**  

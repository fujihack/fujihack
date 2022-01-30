# Notes/Interesting Findings

- Once you update to the latest version, you won't be able  
to install the same firmware file. (there is a workaround)  

- You can modify the header to set the  
firmware update version. When I incremented tje number by  
one, I could update a new firmware, but the new version doesn't  
update the internal number, which is a plus.  

- Additionally, the firmware numbers (X.XX) are printed in hex on  
the camera. The firmware is invalid if the hex number has any letters.
  
- Both firmware numbers cannot be bigger than `0x99`.  

- Code is 32 bit ARM (not thumb)  

- The firmware includes SQLite and some sql code. Not sure why.  

- Unlike the cameras described in https://chdk.setepontos.com/index.php?topic=6484.0, the camera I have  
does not appear to have any batch scripting or hidden menu, as far as I know.  

- The code includes "A:\DCAA\auto_act.scr". Is this some kind of script? Making the file on the SD  
card doesn't seem to do anything.  
EDIT: the fujifilm firmware update utility seems to contain `AUTO_ACT.SCR`  
next to `FPUPDATE.DAT`. Still creating the file does not appear to do anything.  
I assume it means "Automatically activated script".  
EDIT:  
I thought it would be a SQLite script, but AUTO_ACT.SCR is on the Fujifilm Z3,  
which doesn't have SQLite or much code at all (4mb firmware). Possibly automatically  
activated code (ARM)?  

- There is a "Happy Birthday!" string in the firmware.  

- These strings suggest there may be a secret menu:  
```
"OSD DEBUG MODE SCREEN SELECT"  
"SCREEN   <UP/DOWN>    : "  
"WARNING  <RIGHT/LEFT> : "  
```
I tried calling the function that references it and nothing happened.

- https://www.fujix-forum.com/threads/strange-folder-on-card.14120/

- 2003-2006 Fujifilm Hacks:  
https://www.dpreview.com/forums/thread/430068  
http://www.digsys.com.au/S602Z/S602Z.html  
Modern Fuji cameras seem to also make references  
to .S3 files.  

- The first few lines of assembly in the firmware file  
do not seem to be executed in the firmware menu.  
It might during firmware updating process, but that is a  
brick garuntee if it doesn't work.  

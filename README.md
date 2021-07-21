# fujifilm-firmware
Fujifilm firmware unpacker

This will only work on modern Fujifilm cameras,  
such as the HS20EXR or the X-T4.  

## Notes:
Once you update to the latest version, you won't be able  
to install the same firmware file.  

You can modify `HEADER_V1` and `HEADER_V2` to set the  
firmware update version. When I incremented `HEADER_V2` by  
one, I could update a new firmware, but the new version doesn't  
update the internal number.

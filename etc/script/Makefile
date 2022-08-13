# For writing files on Unix
drive=/media/daniel/disk

all:
	awk 'sub("$$", "\r")' AUTO_ACT.SCR > $(drive)/DCAA/AUTO_ACT.SCR
	umount $(drive)

drive:
	echo Please mount drive

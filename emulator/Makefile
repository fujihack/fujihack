# Doesn't have compressed firmware
MODEL?=hs20exr

all:
	wget -nc https://github.com/AlexAltea/unicorn.js/releases/download/v1.0/unicorn-arm.min.js
	cd ..; make lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT
	node main.js

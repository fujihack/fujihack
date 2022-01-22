# Doesn't have compressed firmware
model?=hs20exr

all: unicorn-arm.min.js ../output
	node main.js

unicorn-arm.min.js:
	curl -ipv4 -O https://github.com/AlexAltea/unicorn.js/releases/download/v1.0/unicorn-arm.min.js

../output:
	cd ..; make lay INPUT_FILE=~/Downloads/FPUPDATE-$(MODEL).DAT

-include ../config.mak

OUT=main.o
OUT+=$(addprefix camlib/src/,operations.o packet.o enums.o enum_dump.o data.o util.o)

OUT_WIN=$(OUT) $(addprefix camlib/src/,winapi.o)
OUT_UNIX=$(OUT) $(addprefix camlib/src/,backend.o libusb.o)

CFLAGS=-I camlib/src/

fuji: $(OUT_UNIX)
	$(CC) $(OUT_UNIX) -lusb-1.0 -o fuji

libwpd.dll:
	wget https://github.com/petabyt/libwpd/releases/download/0.1.1/libwpd_x64.dll -O libwpd.dll

fuji.exe: $(OUT_WIN)
	x86_64-w64-mingw32-gcc $(OUT_WIN) libwpd.dll -o fuji.exe

clean:
	$(RM) camlib/src/*.o fuji fuji.exe 

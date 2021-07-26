CC = tcc

asm:
	@${CC} firm.c -o firm
	@./firm asm
	@rm firm

pack:
	@${CC} firm.c -o firm
	@./firm pack
	@rm firm

unpack:
	@${CC} firm.c -o firm
	@./firm unpack
	@rm firm
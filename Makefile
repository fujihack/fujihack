# Target:
# p     pack firmware file
# u     unpack firmware file
t ?= p

all:
	@rm -rf FPUPDATE.DAT
	@touch FPUPDATE.DAT output

	@${CC} firm.c -o firm.o
	@./firm.o ${t}
	@rm -rf *.o

diff:
	@xxd FPUPDATE.DAT > a
	@xxd FPUPDATE-orig.DAT > b
	-@diff a b
	@rm -rf a b

clean:
	@rm -rf a b
	@rm -rf *.o
	@rm -rf FPUPDATE.DAT
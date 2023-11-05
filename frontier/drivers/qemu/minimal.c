/*

https://github.com/qemu/qemu/blob/master/hw/arm/versatilepb.c
https://developer.arm.com/documentation/dui0224/i/

$ make ARCH=qemu os.bin
$ qemu-system-arm -M versatilepb -m 1M -nographic -kernel os.bin
*/

int entry() {
	uart_str("Hello world!\n");
	uart_str("Hello world!\n");
}

int exit() {

}

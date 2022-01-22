var fs = require("fs");
var cp = require("child_process");
var process = require("process");

var CC = "arm-none-eabi";

main();

function system(string) {
	var r = cp.execSync(string);
	process.stdout.write(String(r));
}

function main() {
	console.log("Loading code...");
	var memory = fs.readFileSync("/home/daniel/Desktop/fujifilm-backup/dump/dump_xf1_0x0");
	var memsize = memory.length;

	// Compile and load test.c directly after output file

	console.log("Compiling test.c ...")
	system(CC + "-gcc test.c -c -ffreestanding -marm -o test.o");
	system(CC + "-ld -Bstatic test.o -Ttext 0x" + memsize.toString(16) + " -o test.elf");
	system(CC + "-objcopy -O binary test.elf test.o");
	// -Ttext 0x" + memsize.toString(16) + "

	var test = fs.readFileSync("test.o");
	var newMemory = Buffer.concat([memory, test])

	console.log("Loading Unicorn...");
	eval(String(fs.readFileSync("unicorn-arm.min.js")));

	// Initialize engine
	var e = new uc.Unicorn(uc.ARCH_ARM, uc.MODE_ARM);

	console.log("allocating memory...");

	// Allocate 50 megabytes of memory
	e.mem_map(0, 50 * 1024000, uc.PROT_ALL);
	e.mem_write(0, newMemory);

	// HS20EXR firmware seems to use this base address
	e.mem_map(0x40000000, 50 * 1024000, uc.PROT_ALL);

	system("ls -l test.o");
	system("rm -rf *.o *.elf");
	
	var begin = newMemory.length - test.length;
	var until = newMemory.length - 4;

	// Give code some stack space
	var err = e.reg_write_i32(uc.ARM_REG_SP, begin + 1000);

	// bx lr to the end of file to trigger VM quit
	e.reg_write_i32(uc.ARM_REG_LR, until);

	console.log("Running VM...");

	try {
		e.emu_start(begin, until, 0, 0);
	} catch (err) {
		console.log(err);
		console.log("LR:\t" + e.reg_read_i32(uc.ARM_REG_LR).toString(16));
		console.log("PC:\t" + e.reg_read_i32(uc.ARM_REG_PC).toString(16));
		for (var i = 0; i < 15; i++) {
			console.log("R" + i + ":\t0x" +
				(e.reg_read_i32(uc["ARM_REG_R" + i]) >>> 0).toString(16)) >> 0;
		}

		return;
	}

	var r0 = e.reg_read_i32(uc.ARM_REG_R0);
	console.log("Return value: ", (r0 >>> 0).toString(16));

	if (r0 < 10) {
		console.log("No string");
		return;
	}

	try {
		var returnString = e.mem_read(r0, 100);
		console.log("Return bytes: " + returnString);
		try {
			console.log("Return string: " + String.fromCharCode.apply(null, returnString));
		} catch {
			console.log("No string");
		}
	} catch {
		console.log("No data");
	}
}

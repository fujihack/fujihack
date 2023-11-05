#include <unicorn/unicorn.h>

#include <emulator.h>

int help() {
	printf(
		"Frontier Emulator\n"
		"-i\tSpecify input file\n"
		"-e\tRun input file in graphical emulator\n"
	);

	return 0;
}

int main(int argc, char *argv[]) {
	char *input = "os.bin";
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] != '-') continue;
		switch (argv[i][1]) {
		case 'e':
			return emulator(input);
		case 'h':
			return help();
		}
	}

	puts("No valid args");
	return 0;
}

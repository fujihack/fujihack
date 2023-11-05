#include <pack.h>

#include "../lib/frozen.h"

int help() {
	printf(
		"Frontier build system utility\n"
		"-i <file>    Specify input file\n"
		"-o <file>   Specify output file\n"
		"-s Append symbols from single relocatable file\n"
		"-a <file> Pack JSON data into app\n"
	);

	return 0;
}

int main(int argc, char *argv[]) {
	char *input = "os.elf";
	char *output = "os.bin";
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] != '-') continue;
		switch (argv[i][1]) {
		case 'i':
			input = argv[i + 1];
			break;
		case 'o':
			output = argv[i + 1];
			break;
		case 's':
			// Append single row of symbols from file
			return add_syms(input, output);
		case 'a': {
			char *content = json_fread(argv[i + 1]);
			struct AppMetaData amd;
			gen_app_meta(&amd, content);
			// TODO: prepend file with metadata
		} break;
		case 'h':
			return help();
		}
	}

	puts("No valid args");
	help();
	return 0;
}

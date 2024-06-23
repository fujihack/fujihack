// Fujihack USB Utility
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <camlib.h>

int fh_cmd(struct PtpRuntime *r, int a, int b);
int test_upload(struct PtpRuntime *r, char *file);
int run_code(struct PtpRuntime *r, char *file);

int ff80_hack(char *arg);
int ff80_dump();

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] != '-') continue;
		switch (argv[i][1]) {
		case '8':
			return ff80_hack(argv[i + 1]);
		case 'd':
			return ff80_dump();
		case 'h':
			puts("-r -s -t -d -h");
			return 0;
		}
	}


	struct PtpRuntime r;
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] != '-') continue;
		switch (argv[i][1]) {
		case 'r':
			return run_code(&r, argv[i + 1]);
		case 's':
			return test_upload(&r, argv[i + 1]);
		case 't':
			return test_hacks(&r);
		}
	}
}

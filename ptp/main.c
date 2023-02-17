#include <stdio.h>
#include <stdint.h>

#include <camlib.h>
#include <ptpbackend.h>
#include <operations.h>
#include <ptp.h>

#define FUJI_HIJACK 0x9805

#define FH_ZERO 4
#define FH_WRITE 5
#define FH_EXEC 6
#define FH_RESET 7
#define FH_SETADDR 8
#define FH_GET 9

int fh_cmd(struct PtpRuntime *r, int a, int b) {
	struct PtpCommand cmd;
	cmd.code = FUJI_HIJACK;
	cmd.param_length = 2;
	cmd.params[0] = a;
	cmd.params[1] = b;

	return ptp_generic_send(r, &cmd);	
}

int run_code(struct PtpRuntime *r, char *file) {
	FILE *f = fopen(file, "rb");
	if (f == NULL) {
		puts("Can't open file");
		return 1;
	}
	
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	printf("File is %d\n", size);

	int ret;
	for (int i = 0; i < size; i++) {
		int b = fgetc(f);
		if (b == EOF) {
			return 1;
		}

		if ((uint8_t)b == 0) {
			ret = fh_cmd(r, FH_ZERO, 255);
		} else {
			ret = fh_cmd(r, FH_WRITE, (uint8_t)b);
		}

		if (ret) {
			puts("IO Error while writing");
			return 1;
		}

		if (ptp_get_return_code(r) != PTP_RC_OK) {
			puts("Response code not OK");
			return 1;
		}

		int percent = 1000 * i / size;
		if (percent % 10 == 0) {
			printf("%d%%\n", percent / 10);
		}
	}

	ret = fh_cmd(r, FH_EXEC, 0);
	if (ret) {
		puts("IO Error while running");
	}

	struct PtpDeviceInfo d;
	ptp_get_device_info(r, &d);
	printf("%s\n", d.extensions);

	return 0;
}

int main(int argc, char *argv[]) {
	struct PtpRuntime r;
	ptp_generic_init(&r);

	if (ptp_device_init(&r)) {
		puts("Couldn't find a device.");
		return 1;
	}

	ptp_open_session(&r);

	fh_cmd(&r, FH_RESET, 0);
	if (ptp_get_return_code(&r) != PTP_RC_OK) {
		puts("Device is unhacked.");
		return 1;
	}

	for (int i = 0; i < argc; i++) {
		if (argv[i][0] != '-') continue;
		switch (argv[i][1]) {
		case 'r':
			return run_code(&r, argv[i + 1]);
		}
	}
}

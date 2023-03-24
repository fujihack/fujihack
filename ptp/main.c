#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <camlib.h>
#include <ptpbackend.h>
#include <operations.h>
#include <ptp.h>

#define PTP_OC_FUJI_SendObjectInfo 0x900c
#define FUJI_UNKNOWN1 0x900d
#define PTP_OC_FUJI_SendObject 0x901d

#define PTP_OC_FujiHack 0x9805

#define FH_ZERO 4
#define FH_WRITE 5
#define FH_EXEC 6
#define FH_RESET 7
#define FH_SETADDR 8
#define FH_GET 9

int fh_cmd(struct PtpRuntime *r, int a, int b) {
	struct PtpCommand cmd;
	cmd.code = PTP_OC_FujiHack;
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

int test_upload(struct PtpRuntime *r, char *file) {
	struct UintArray *ids;

	int ret = ptp_get_storage_ids(r, &ids);
	if (ret) {
		return ret;
	}

	FILE *f = fopen(file, "rb");
	if (f == NULL) {
		puts("Can't open file");
		return 1;
	}
	
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = "AUTO_ACT.SCR";

	char info[256];
	memset(info, 0, sizeof(info));
	((uint32_t *)(info))[0] = ids->data[0];
	((uint32_t *)(info))[1] = 0x3002;
	((uint32_t *)(info))[2] = size;
	memset(info + 12, 0, 40);

	((char *)(info + 12 + 40))[0] = '\r';
	for (int i = 0; string[i] != '\0'; i++) {
		((char *)(info + 12 + 40 + 1))[i * 2] = string[i];
		((char *)(info + 12 + 40 + 1))[i * 2 + 1] = '\0';
	}

	int length = 12 + 40 + 1 + (strlen(string) * 2) + 2;

	struct PtpCommand cmd;
	cmd.code = PTP_OC_FUJI_SendObjectInfo;
	cmd.param_length = 0;

	int x = ptp_generic_send_data(r, &cmd, info, 256);
	printf("Result: %X\n", x);
	printf("Result: %X\n", ptp_get_return_code(r));

	void *file_data = malloc(size);
	fread(file_data, size, 1, f);

	cmd.code = PTP_OC_FUJI_SendObject;
	cmd.param_length = 0;

	x = ptp_generic_send_data(r, &cmd, file_data, size);
	printf("Result: %X\n", x);
	printf("Result: %X\n", ptp_get_return_code(r));
	printf("Wrote %d\n", size);

	fclose(f);

	ptp_close_session(r);
	ptp_device_close(r);
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
		case 's':
			return test_upload(&r, argv[i + 1]);
		}
	}
}

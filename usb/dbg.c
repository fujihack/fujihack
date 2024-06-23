// Copyright 2024 tiredboffin@gmail.com
#include <byteswap.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <libusb.h>

static libusb_context *ctx;
static libusb_device_handle *handle;
static int ep_in, ep_out, ep_int;

int ff80_open() {
	libusb_init(&ctx);

	libusb_device **list;
	ssize_t count = libusb_get_device_list(ctx, &list);

	struct libusb_device_descriptor desc;
	struct libusb_config_descriptor *config;
	const struct libusb_interface *interf;
	const struct libusb_interface_descriptor *interf_desc;

	printf("Found %lu devices\n", count);

	libusb_device *dev = NULL;
	for (int i = 0; i < (int)count; i++) {
		int rc = libusb_get_device_descriptor(list[i], &desc);
		if (rc) {
			perror("libusb_get_device_descriptor");
			return -1;
		}

		if (desc.bNumConfigurations == 0) {
			continue;
		} 

		rc = libusb_get_config_descriptor(list[i], 0, &config);
		if (rc) {
			perror("libusb_get_config_descriptor");
			return -1;
		}

		if (config->bNumInterfaces == 0) {
			continue;
		}

		interf = &config->interface[0];
		if (interf->num_altsetting == 0) {
			continue;
		}

		interf_desc = &interf->altsetting[0];

		printf("Vendor ID: %X, Product ID: %X\n", desc.idVendor, desc.idProduct);

		if (desc.idVendor == 0x4cb && desc.idProduct == 0xff80) {
			dev = list[i];
			break;
		}

		libusb_free_config_descriptor(config);
	}

	if (dev == NULL) {
		return -1;
	}

	const struct libusb_endpoint_descriptor *ep = interf_desc->endpoint;
	for (int i = 0; i < interf_desc->bNumEndpoints; i++) {
		if (ep[i].bmAttributes == LIBUSB_ENDPOINT_TRANSFER_TYPE_BULK) {
			if (ep[i].bEndpointAddress & LIBUSB_ENDPOINT_IN) {
				ep_in = ep[i].bEndpointAddress;
				printf("Endpoint IN addr: 0x%X\n", ep[i].bEndpointAddress);
			} else {
				ep_out = ep[i].bEndpointAddress;
				printf("Endpoint OUT addr: 0x%X\n", ep[i].bEndpointAddress);
			}
		} else if (ep[i].bmAttributes == LIBUSB_ENDPOINT_TRANSFER_TYPE_INTERRUPT) {
			ep_int = ep[i].bEndpointAddress;
			printf("Endpoint INT addr: 0x%X\n", ep[i].bEndpointAddress);	
		}
	}

	libusb_free_config_descriptor(config);
	int rc = libusb_open(dev, &handle);
	libusb_free_device_list(list, 0);
	if (rc) {
		perror("usb_open() failure");
		return -1;
	} else {
		if (libusb_set_auto_detach_kernel_driver(handle, 0)) {
			perror("libusb_set_auto_detach_kernel_driver");
			return -1;
		}

		if (libusb_claim_interface(handle, 0)) {
			perror("usb_claim_interface() failure");
			libusb_close(handle);
			return -1;
		}
	}

	return 0;
}

#pragma pack(push, 1)
struct FFControlPacket {
	uint8_t cmd;
	uint8_t cmd2;
	uint32_t b;
	uint32_t size;
	uint16_t sid;
};
struct FFSessionInfo {
	uint32_t sid;
	uint32_t max;
};
struct FFMemOp {
	uint32_t cmd;
	uint8_t res0[12];
	uint32_t cmd2;
	uint32_t params[4];
};
#pragma pack(pop)

static int ffcontrol_write(void *data, size_t size) {
	return libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_OTHER, 0, 0, 0, data, size, 200);
}

static int ffbulk_read(void *in, int length) {
	int transferred;
	int rc = libusb_bulk_transfer(
		handle,
		ep_in,
		in, length, &transferred, 200);
	if (rc < 0) return rc;
	return transferred;
}

static int ffbulk_write(void *out, int length) {
	int transferred;
	int rc = libusb_bulk_transfer(
		handle,
		ep_out,
		out, length, &transferred, 200);
	if (rc < 0) return rc;
	return transferred;
}

int ff80_ping(int sid) {
	struct FFControlPacket pk = {0};
	pk.cmd = 0xc2;
	pk.cmd2 = 0x0;
	pk.size = __bswap_32(0x2);
	pk.sid = __bswap_16(sid);
	int rc = ffcontrol_write(&pk, sizeof(pk));

	uint16_t buf;
	rc = ffbulk_read(&buf, 2);
	assert(rc == 2);
	printf("Ping: %d\n", buf);

	return 0;
}

int ff80_write_cmd(int sid, void *data, int size) {
	struct FFControlPacket pk = {0};
	pk.cmd = 0xd0;
	pk.cmd2 = 0x0;
	pk.size = __bswap_32(size);
	pk.sid = __bswap_16(sid);

	int rc = ffcontrol_write(&pk, sizeof(pk));
	assert(rc == sizeof(pk));

	rc = ffbulk_write(data, size);
	assert(rc == size);

	return 0;	
}

int ff80_read_cmd(int sid, void *data, int size) {
	struct FFControlPacket pk = {0};
	pk.cmd = 0xd1;
	pk.cmd2 = 0x0;
	pk.size = __bswap_32(size);
	pk.sid = __bswap_16(sid);
	int rc = ffcontrol_write(&pk, sizeof(pk));

	rc = ffbulk_read(data, size);
	printf("Read %d\n", rc);
	assert(rc == size);

	return 0;
}

int ff80_open_session(int *sid) {
	struct FFControlPacket pk = {0};
	pk.cmd = 0xc0;
	pk.cmd2 = 0x0;
	pk.size = __bswap_32(0x8);
	pk.sid = __bswap_16(0x0);
	int rc = ffcontrol_write(&pk, sizeof(pk));

	char buffer[128];
	rc = ffbulk_read(buffer, 8);
	assert(rc == 8);
	struct FFSessionInfo *i = (struct FFSessionInfo *)buffer;

	(*sid) = i->sid;

	return 0;
}

int ff80_close_session(int sid) {
	struct FFControlPacket pk = {0};
	pk.cmd = 0xc4;
	pk.cmd2 = 0x0;
	pk.size = __bswap_32(0x2);
	pk.sid = __bswap_16(sid);
	int rc = ffcontrol_write(&pk, sizeof(pk));

	uint16_t buf;
	rc = ffbulk_read(&buf, 2);
	assert(rc == 2);

	return 0;
}


int ff80_cmd(int sid, uint32_t cmd, uint32_t cmd2, uint32_t *params, void *data, size_t size) {
	int of = 36;
	char buffer[512] = {0};
	struct FFMemOp *m = (struct FFMemOp *)buffer;
	m->cmd = cmd;
	m->cmd2 = cmd2;
	memcpy(m->params, params, 16);
	if (size) {
		memcpy(buffer + of, data, size);
		of += size;
	}

	return ff80_write_cmd(sid, buffer, of);
}

int ff80_read_eep(int sid, void *buffer, uint32_t of, int size) {
	uint32_t params[4] = {1, 0, of, size};
	ff80_cmd(sid, 0x1a0002, 2, params, NULL, 0);

	char temp[512];

	int rc = ff80_read_cmd(sid, temp, 36 + size);

	uint32_t *codes = (uint32_t *)temp;
	printf("err = %x\n", codes[1]);

	memcpy(buffer, temp + 36, size);

	return rc;
}

int ff80_write_eep_byte(int sid, uint32_t of, uint8_t byte) {
	char data[1] = {byte};

	uint32_t params[4] = {1, 0, of, 1};
	ff80_cmd(sid, 0x1a0002, 3, params, data, 1);

	char temp[512];
	int rc = ff80_read_cmd(sid, temp, 36);

	uint32_t *codes = (uint32_t *)temp;
	printf("err = %x\n", codes[1]);

	return rc;	
}

int ff80_read_mem(int sid, void *buffer, uint32_t of, int size) {
	uint32_t params[4] = {0, 0, of, size};
	ff80_cmd(sid, 0x200001, 2, params, NULL, 0);

	char temp[512];

	int rc = ff80_read_cmd(sid, temp, 36 + size);
	printf("Read %d bytes\n", rc);

	uint32_t *codes = (uint32_t *)temp;
	printf("err = %x\n", codes[1]);

	memcpy(buffer, temp + 36, size);

	return rc;
}

int ff80_write_mem(int sid, void *buffer, int of, int size) {
	uint32_t params[4] = {1, 0, of, size};
	ff80_cmd(sid, 0x200001, 3, params, buffer, size);

	char temp[512];
	int rc = ff80_read_cmd(sid, temp, 36);

	uint32_t *codes = (uint32_t *)temp;
	printf("err = %x\n", codes[1]);

	return rc;	
}

int ff80_press_key(int sid) {

	char string[] = "CMD UP";

	uint32_t params[4] = {0, 0, 0, sizeof(string)};
	ff80_cmd(sid, 0x200001, 5, params, string, strlen(string));

	char temp[512];
	int rc = ff80_read_cmd(sid, temp, 36);

	uint32_t *codes = (uint32_t *)temp;
	printf("presskey err = %x, %x\n", codes[2], codes[1]);
	return 0;
}

int ff80_init() {
	int rc = ff80_open();
	if (rc) {
		printf("ff80 device not found\n");
		return 1;
	}

	int sid;

	ff80_open_session(&sid);
	printf("Sid: %d\n", sid);
	ff80_ping(sid);

	uint8_t buffer[512];
	ff80_write_eep_byte(sid, 0xf7, 0x1);
	ff80_read_eep(sid, buffer, 0xf7, 1);
	printf("New byte: %x\n", buffer[0]);

#if 0
	ff80_read_eep(sid, buffer, 0xf7, 1);
	printf("New: %x\n", buffer[0]);

	ff80_read_mem(sid, buffer, 0x40000000, 250);
	for (int i = 0; i < 250; i++) {
		printf("%02X ", buffer[i]);
	} puts("");
#endif

	return sid;
}

int ff80_dump() {
	int rc = ff80_open();
	if (rc) {
		printf("ff80 device not found\n");
		return 1;
	}

	int sid;

	ff80_open_session(&sid);
	printf("Sid: %d\n", sid);
	ff80_ping(sid);

	uint8_t buffer[512];
	ff80_write_eep_byte(sid, 0xf7, 0x1);
	ff80_read_eep(sid, buffer, 0xf7, 1);
	printf("New byte: %x\n", buffer[0]);

	// ff80_read_mem(sid, buffer, 0x80000000, 100);
	// for (int i = 0; i < 100; i++) {
	// 	printf("%02X ", buffer[i]);
	// } puts("");

#if 1
	FILE *f = fopen("dump", "wb");

	int of = 0;
	for (int i = 0; i < 32000 / 100; i++) {
		ff80_read_mem(sid, buffer, 0x80000000 + of, 100);
		fwrite(buffer, 1, 100, f);
		of += 100;
	}

	fclose(f);
#endif

	ff80_close_session(sid);

	return sid;

}

int ff80_hack(char *file) {
	int sid = ff80_init();

	FILE *f = fopen(file, "rb");
	if (f == NULL) {
		puts("Can't open file");
		return 1;
	}
	
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	uint8_t *buffer = malloc(512);
	fread(buffer, 1, size, f);

	uint32_t new_addr = 0x03000000;
	ff80_write_mem(sid, &new_addr, 0x0113c55c, 4);

	int sent = 0;
	while (sent <= size) {
		puts("Write req");
		int cur = size;
		if (cur > 100) cur = 100;
		ff80_write_mem(sid, buffer + sent, new_addr + sent, cur);
		sent += cur;
	}

	ff80_read_mem(sid, buffer, 0x0138e569, 100);
	for (int i = 0; i < 100; i++) {
		printf("%02X ", buffer[i]);
	} puts("");

	ff80_press_key(sid);

	ff80_close_session(sid);

	fclose(f);

	return 0;
}

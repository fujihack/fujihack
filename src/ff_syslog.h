// Documents Fujifilm's "Syslog"
#ifndef SYSLOG_H
#define SYSLOG_H

#include <stdint.h>

#pragma pack(push, 1)

struct SyslogHeader {
	char msg[0x14]; // only this is null terminated
	uint16_t of_0x14;
	uint8_t of_0x16;
	uint8_t of_0x17;
	uint16_t of_0x18;
	uint16_t of_0x1a;
	uint16_t curr_msg;
	uint8_t blah[20];
	uint32_t of_0x30;
};

enum SyslogMsgType {
	SYSLOG_MSG_SIG = 0xf,
	SYSLOG_MSG_STR = 0x72,
};

struct SyslogMsg {
  // addressed in uint32_t and uint8_t form
  uint8_t type;
  uint8_t of_0x1; // return from thread code
  uint8_t of_0x2; // val @ fffa9c08
  uint8_t of_0x3; // 0
  
  uint32_t id; // magic number??
  
  char msg[8];
}

#pragma pack(pop)

#endif

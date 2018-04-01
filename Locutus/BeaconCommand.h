#ifndef BEACONCOMMAND_H
#define BEACONCOMMAND_H
#include <stdint.h>

#include "TLV.h"
#include "List.h"

typedef struct _BeaconCommand_T {
	ListEntry_T listEntry;
	Header_T header;
} BeaconCommand_T;

typedef struct _ChangeKnockAddress_T {
	uint8_t protocol;
	uint16_t port;
	uint16_t length;
	uint8_t hostname[0];
} ChangeKnockAddress_T;

typedef struct _ChangeBeaconAddress_T {
	uint8_t protocol;
	uint16_t port;
	uint16_t length;
	uint8_t hostname[0];
} ChangeBeaconAddress_T;

typedef struct _ChangeKnockCounts_T {
	uint32_t count;
} ChangeKnockCounts_T;

typedef struct _ChangeCommDelay_T {
	uint32_t seconds;
} ChangeCommDelay_T;

#endif

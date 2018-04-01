#ifndef TLV_H
#define TLV
#include <stdint.h>
typedef struct _Header_T {
	uint32_t type;
	uint32_t length;
} Header_T;

typedef struct _TLV_T {
	uint32_t type;
	uint32_t length;
	uint8_t value[0];
} TLV_T;

#endif

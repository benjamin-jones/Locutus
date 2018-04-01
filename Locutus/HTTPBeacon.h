#ifndef HTTPBEACON_H
#define HTTPBEACON_H
#include "BeaconCommand.h"
#include <Windows.h>

BeaconCommand_T* TryHTTPBeacon(wchar_t* hostname);

#endif

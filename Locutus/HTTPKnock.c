#include <Windows.h>
#include <winhttp.h>
#include "Debug.h"
#include "HTTPKnock.h"

BOOL TryHTTPKnock(wchar_t* hostname)
{
	HINTERNET hSession = NULL;
	HINTERNET hConnect = NULL;
	HINTERNET hRequest = NULL;
	BOOL bResults = FALSE;
	BOOL result = FALSE;

	hSession = WinHttpOpen(L"Locutus v0.1", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (!hSession) {
		debug("Could not open HTTP session");
		goto Error;
	}

	hConnect = WinHttpConnect(hSession, hostname, INTERNET_DEFAULT_HTTPS_PORT, 0);

	if (!hConnect) {
		debug("Connection failed: %d", GetLastError());
		goto Error;
	}

	hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/robots.txt", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

	if (!hRequest) {
		debug("Failed to open request");
		goto Error;
	}

	bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

	if (!bResults) {
		debug("Send request failed %d", GetLastError());
		goto Error;
	}

	bResults = WinHttpReceiveResponse(hRequest, NULL);

	if (!bResults) {
		debug("No response received");
		goto Error;
	}

	result = TRUE;
Error:
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
	return result;
}
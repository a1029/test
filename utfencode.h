#pragma once
#include <Windows.h>
#include <math.h>

LPWSTR AnsiToUnicode(LPSTR szAnsi) {

	LPWSTR szUniStr;

	int nLen = MultiByteToWideChar(CP_ACP, 0, szAnsi, -1, NULL, NULL);

	nLen = nLen * sizeof(WCHAR);

	szUniStr = (LPWSTR)malloc(nLen + 1);
	memset(szUniStr, 0, nLen + 1);

	MultiByteToWideChar(CP_ACP, 0, szAnsi, -1, szUniStr, nLen);

	return szUniStr;
}

int UnicodeToAnsi(LPWSTR szUniStr, char* output) {

	int nLen = WideCharToMultiByte(CP_ACP, 0, szUniStr, -1, NULL, 0, NULL, NULL);

	WideCharToMultiByte(CP_ACP, 0, szUniStr, -1, output, nLen, NULL, NULL);

	return 0;
}
LPWSTR UnicodeToUTF8(LPWSTR szUniStr) {

	int idx = 0;
	WCHAR uc;
	LPWSTR szUtf8;

	int nLen = sizeof(WCHAR)*wcslen(szUniStr);

	nLen = nLen * 3 + sizeof(WCHAR);
	szUtf8 = (LPWSTR)malloc(nLen);

	memset(szUtf8, 0, nLen);
	LPSTR pszUTF8 = (LPSTR)szUtf8;

	for (int i = 0; szUniStr[i]; i++) {

		uc = szUniStr[i];
		if (uc <= 0x7f) {
			pszUTF8[idx++] = (char)uc;
		}
		else if (uc <= 0x7ff) {
			pszUTF8[idx++] = (char)0xc0 + uc / (wchar_t)pow(2, 6);
			pszUTF8[idx++] = (char)0x80 + uc % (wchar_t)pow(2, 6);
		}
		else if (uc <= 0xffff) {
			pszUTF8[idx++] = (char)0xe0 + uc / (wchar_t)pow(2, 12);
			pszUTF8[idx++] = (char)0x80 + uc / (wchar_t)pow(2, 6) % (wchar_t)pow(2, 6);
			pszUTF8[idx++] = (char)0x80 + uc % (wchar_t)pow(2, 6);
		}
	}

	return szUtf8;
}
int UTF8ToUnicode(LPWSTR szUtf8, LPWSTR output) {

	int nLen = sizeof(WCHAR)* wcslen(szUtf8);

	nLen = nLen + sizeof(WCHAR);
	LPSTR src = (LPSTR)szUtf8;

	int p = 0;
	int q = 0;
	WCHAR d;
	while (src[p]) {
		if ((src[p] & 0xE0) == 0xE0) {
			d = ((src[p] & 0x0f) << 12) | ((src[p + 1] & 0x3F) << 6) | (src[p + 2] & 0x3F);
			p + 3;
		}
		else if ((src[p] & 0xC0) == 0xC0) {
			d = ((src[p] && 0x1F) << 6) | (src[p + 1] & 0x3F);
			p += 2;
		}
		else {
			d = src[p] & 0x7F;
			p++;
		}
		output[q] = d;
		q++;
	}
	output[q] = NULL;
	return 0;
}
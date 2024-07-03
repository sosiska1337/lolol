
#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include "cServer.h"

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};


std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Copy(const char* text)
{
	OpenClipboard(NULL);
	EmptyClipboard();
	HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
	char* ptr = (char*)GlobalLock(hText);
	strcpy_s(ptr, strlen(text) + 1, text);
	GlobalUnlock(hText);
	SetClipboardData(CF_TEXT, hText);
	CloseClipboard();
	GlobalFree(hText);
}

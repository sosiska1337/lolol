#pragma once
#include "cHttp.h"
#include <algorithm>
#include <time.h>
#include <vector>
#include <sstream>
#include "KeyGen.h"

struct _SETTING
{
	std::string   szHost = "h96733zj.beget.tech/index.php";
	std::string   szVersion = "";
	INT Protocol = HTTP_CLEAR;
}SETTING;



std::string toHex(const char* pchData, int count)
{
	std::string s;
	for (int i = 0; i < count; ++i) {
		unsigned char ch = pchData[i];
		unsigned char lo = ch % 16;
		unsigned char hi = ch / 16;
		s.push_back((hi < 10) ? (hi + 0x30) : (hi + 87));
		s.push_back((lo < 10) ? (lo + 0x30) : (lo + 87));
	}
	return s;
}

struct _USERINFO
{
	std::string szKey;
	_USERINFO()
	{
		szKey = GetSerial();
	}
}USERINFO;

void Version()
{
	CHTTPSession* pHttp = new CHTTPSession;
	std::string szAnswer;

	pHttp->Request(HTTP_POST, SETTING.Protocol, SETTING.szVersion, szAnswer, "", 0);
	delete pHttp;
	if (szAnswer.compare("Version 1.0") == 0)
	{
		std::cout << "Ваша версия: " << szAnswer.c_str() << std::endl;
	}
	else
	{
		MessageBox(0, (LPCSTR)"Вышла новая версия ", (LPCSTR)szAnswer.c_str(), MB_ICONASTERISK);
		exit(0);
	}
}

std::string DataTime(std::string key)
{
	CHTTPSession* pHttp = new CHTTPSession;
	std::string szAnswer;
	pHttp->Request(HTTP_POST, SETTING.Protocol, SETTING.szHost, szAnswer, "MESSAGE=DAYS&USERKEY=" + key, 0);
	delete pHttp;
	szAnswer = u8"Active: " + szAnswer;
	return szAnswer.c_str();
}
char* settime(struct tm* u)
{
	char s[40];
	char* tmp;
	for (int i = 0; i < 40; i++) s[i] = 0;
	int length = strftime(s, 40, "%S%M", u);
	tmp = (char*)malloc(sizeof(s));
	strcpy(tmp, s);
	return(tmp);
}
BOOL StartKey(std::string szKey)
{
	CHTTPSession* pHttp = new CHTTPSession;
	std::string szAnswer;

	pHttp->Request(HTTP_POST, SETTING.Protocol, SETTING.szHost, szAnswer, "MESSAGE=LOGIN&USERKEY=" + szKey, 0);
	delete pHttp;
	if (szAnswer.compare("USER NOT EXISTS") == 0)
	{
		return FALSE;
	}
	else
		if (szAnswer.compare("LICENSE EXPIRED") == 0)
		{
			return FALSE;
		}
		else
			if (szAnswer.compare("FALSE USER DATA") == 0)
			{
				return FALSE;
			}
			else
			{
				struct tm* u;
				char* f;
				const time_t timer = time(NULL);
				u = localtime(&timer);
				f = settime(u);
				char* hash = strcat((char*)GetHashSerialKey().c_str(), f);
				cout << "client: " << hash << endl;
				cout << "server: " << szAnswer << endl;
				if (szAnswer.compare(hash) == 0)
				{
					return TRUE;
				}
			}
	return FALSE;
}
#pragma warning(disable : 4530)
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN


#define safe_read(Addr, Type) driver::read<Type>(g_Sock, g_PID, Addr)
#define safe_write(Addr, Data, Type) driver::write<Type>(g_Sock, g_PID, Addr, Data)
#define safe_memcpy(Dst, Src, Size) driver::write_memory(g_Sock, g_PID, Dst, driver::read_memory(g_Sock, g_PID, Src, 0, Size), Size)

#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <iostream>
#include <string>
#include <cassert>
#include <emmintrin.h>
#include <winioctl.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <windows.h>

#include "driver.h"
#include "Offsets.h"

SOCKET g_Sock;
DWORD g_PID;
uint64_t u_Base;
uint64_t g_Base;
bool g_Locked;

#include "sdk_new/math.h"
#include "vars/vars.h"

#include "sdk/game_sdk.h"
#include "cheat_funcs/MiscFuncs.h"
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <WinInet.h>
#include <urlmon.h>
#pragma comment (lib, "Wininet.lib")
#pragma comment (lib, "urlmon.lib")



DWORD GetPID(const std::wstring& procname);
DWORD RPid();

#define AllocCons 0

void EntityZaLoop();
void MainLoop();
BasePlayer* Fetch();
BasePlayer* AimEntity = nullptr;

//struct player_struct {
//	Vector2 head_screen;
//};
//std::vector<player_struct> player_list = {};

bool drawlerstarsxd = false;
bool RPidSuccess = false;

long long firstentry = 0;
UINT64 TodCycle = 0;


#include <Windows.h>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <vector>
#include <Wininet.h>
#include <Dwmapi.h>

#include "junk.h"
#include "cheat_funcs/AimFuncs.h"
#include "xorstr.h"
#include "xor.h"
#include "instr.h"

using namespace std;

std::string xor_decode(std::string data, std::string key)
{
	int g = key.length();
	int r = data.length();
	string ff = "";
	for (int i = 0; i < r; i++)
	{
		ff += data[i] ^= key[i % g];
	}
	return ff;
}

string replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

void randomizetitle()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> distr(0, 51);
	std::string name = xorstr("");
	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (int i = 0; i < 15; ++i)
	{
		name = name + alphabet[distr(mt)];
		SetConsoleTitleA(xorstr(name.c_str()));
	}
}

namespace {
	std::string const default_chars = xorstr("abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
}

std::string random_string(size_t len = 10, std::string const& allowed_chars = default_chars) {
	std::mt19937_64 gen{ std::random_device()() };

	std::uniform_int_distribution<size_t> dist{ 0, allowed_chars.length() - 1 };

	std::string ret;

	std::generate_n(std::back_inserter(ret), len, [&] { return allowed_chars[dist(gen)]; });
	return ret;
}


void SetColour(int ForgC);
void Navigation();
void Switch(int index);
void UpdateMenu();

//const int aim = 0;
const int norec = 0;
const int nosprd = 1;
const int FastEoka = 2;
const int FA = 3;
const int longneck = 4;	 
const int ESP = 5;	
const int spider = 6;
const int admin = 7;
const int thickbullet = 8; //CustomFovBool
const int cf = 9;


//const int One55 = 8;
//const int One4 = 9;
//const int One7 = 10;
//const int One8 = 11;
//const int One9 = 12;
//const int One91 = 13;
//const int One971 = 14;
//
//const int One9711 = 14;
int M_Index = 0;
int Changes = 0;

bool updated = false;
bool lineesp = false;


BasePlayer* Player;

string bools[2] = { xorstr("[ - ]"), xorstr("[ + ]") };

void SetColour(int ForgC) // got online
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void Navigation()
{
	//for (int i = 2; i < 180; i++)
	//{
	//	if (GetAsyncKeyState(i) & 0x8000)
	//	{		  
	//		switch (i)
	//		{
	//		case 40: // UP ARROW
	//			if (M_Index < 12)
	//				M_Index++;
	//			Changes++;
	//			updated = true;
	//			break;
	//		case 38: // DOWN ARROW
	//			if (M_Index > 0)
	//				M_Index--;
	//			Changes++;
	//			updated = true;
	//			break;
	//		case 37: // LEFT ARROW
	//			Switch(M_Index);
	//			Changes++;
	//			updated = true;
	//			break;
	//		case 39: // RIGHT ARROW
	//			Switch(M_Index);
	//			Changes++;
	//			updated = true;
	//			break;
	//		}
	//	}
	//}

		  if ( GetAsyncKeyState ( 40 ) & 0x8000 ) 
               { 
			  if ( M_Index <= 9 )
				  M_Index++;
			  Changes++;
			  updated = true;
			  
          }
else if ( GetAsyncKeyState ( 38 ) & 0x8000 )// DOWN ARROW
{
		  if ( M_Index >= 0 )
			  M_Index--;
		  Changes++;
		  updated = true;
}

else if ( GetAsyncKeyState ( 37 ) & 0x8000 )// DOWN ARROW
			  {
			  Switch ( M_Index );
			  Changes++;
			  updated = true;
			  }

else if ( GetAsyncKeyState ( 39 ) & 0x8000 )// DOWN ARROW
			  {
			  Switch ( M_Index );
			  Changes++;
			  updated = true;
			  }

	//for ( int i = 2; i < 180; i++ )
	//	{
	//	if ( GetAsyncKeyState ( i ) & 0x8000 )
	//		{
	//		switch ( i )
	//			{
	//			case 40: // UP ARROW
	//			if ( M_Index < 12 )
	//				M_Index++;
	//			Changes++;
	//			updated = true;
	//			break;
	//			case 38: // DOWN ARROW
	//			if ( M_Index > 0 )
	//				M_Index--;
	//			Changes++;
	//			updated = true;
	//			break;
	//			case 37: // LEFT ARROW
	//			Switch ( M_Index );
	//			Changes++;
	//			updated = true;
	//			break;
	//			case 39: // RIGHT ARROW
	//			Switch ( M_Index );
	//			Changes++;
	//			updated = true;
	//			break;
	//			}
	//		}
	//	}
}


void Switch(int index)
{	
	if (index == norec )
	{
		AntiRecoil = !AntiRecoil;
	}

	if (index == FA)
	{
		Automatic = !Automatic;
	}

	if (index == FastEoka)
	{
		SuperEoka = !SuperEoka;
	}
	//if (index == aim)
	//{
	//	AimBot = !AimBot;
	//}
	if (index == spider)
	{
		SpiderMan = !SpiderMan;
	}

	//if (index == One3)
	//{
	//	AntiRecoil = !AntiRecoil;
	//}
	if (index == nosprd)
	{
		AntiSpread = !AntiSpread;
	}
	if (index == admin)
	{
		FakeAdmin = !FakeAdmin;
	}
	//if (index == cf)
	//{
	//	if (GetAsyncKeyState(37))
	//	{
	//		if (CustomFov > 90)
	//		{
	//			CustomFov--;
	//			CustomFov--;
	//			CustomFov--;
	//			CustomFov--;
	//			CustomFov--;
	//		}
	//	}
	//	else if (GetAsyncKeyState(39))
	//	{
	//		if (CustomFov < 120)
	//		{
	//			CustomFov++;
	//			CustomFov++;
	//			CustomFov++;
	//			CustomFov++;
	//			CustomFov++;
	//		}
	//	}
	//}
	if (index == thickbullet)
	{
		BigBullet = !BigBullet;
	}

	if (index == cf)
	{
		if (GetAsyncKeyState(37))
		{
			if (CustomFov > 90)
			{
				CustomFov--;
			}
		}
		else if (GetAsyncKeyState(39))
		{
			if (CustomFov < 120)
			{
				CustomFov++;
			}
		}
	}
//	if (index == dist)
//	{
//		if (GetAsyncKeyState(37))
//		{
//			if (Range > 1)
//			{
//				Range--;
//				Range--;
//				Range--;
//				Range--;
//				Range--;
//Range--;
//				Range--;
//				Range--;
//				Range--;
//				Range--;
//			}
//		}
//		else if (GetAsyncKeyState(39))
//		{
//			if (Range < 300)
//			{
//				Range++;
//                Range++;
//				Range++;
//				Range++;
//				Range++;
//				Range++;
//				Range++;
//				Range++;
//				Range++;
//				Range++;
//			}
//		}
//	}
	if (index == longneck)
	{
		LongNeck = !LongNeck;
	}
	if (index == ESP )
	{
		RCS = !RCS;
	}
	//if (index == One8)
	//{
	//	FastBullet = !FastBullet;
	//}
	


}

void UpdateMenu()
{
	int temp = -1;
	if (temp != Changes)
	{
		temp = Changes;
		system(xorstr("cls"));
		SetColour(11);
		cout << xorstr("                                                    MINOKY ") << endl;		//		MINOKY


		if ( M_Index == norec )
			{
			SetColour ( 11 );
			cout << xorstr ( " NoRecoil " ) << bools[AntiRecoil] << endl;
			}
		else
			{
			SetColour ( 13 );
			cout << xorstr ( " NoRecoil " ) << bools[AntiRecoil] << endl;
			}

		if (M_Index == nosprd)
		{
			SetColour(11);
			cout << xorstr(" NoSpread ") << bools[AntiSpread] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" NoSpread ") << bools[AntiSpread] << endl;
		}

		if (M_Index == FastEoka)
		{
			SetColour(11);
			cout << xorstr(" Super Eoka ") << bools[SuperEoka] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" Super Eoka ") << bools[SuperEoka] << endl;
		}

		if (M_Index == FA)
		{
			SetColour(11);
			cout << xorstr(" Full Auto ") << bools[Automatic] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" Full Auto ") << bools[Automatic] << endl;
		}
		//if (M_Index == aim)
		//{
		//	SetColour(10);
		//	cout << xorstr(" AimBot(LKM) = ") << bools[AimBot] << endl;
		//}
		//else
		//{
		//	SetColour(15);
		//	cout << xorstr(" AimBot(LKM) = ") << bools[AimBot] << endl;
		//}
		//if (M_Index == One91)
		//{
		//	SetColour(10);
		//	cout << xorstr(" Smooth aimbot  = ") << smoth << endl;
		//}
		//else
		//{
		//	SetColour(15);
		//	cout << xorstr(" Smooth aimbot = ") << smoth << endl;
		//}
		/*if (M_Index == fov)
		{
			SetColour(10);
			cout << xorstr(" Fov  = ") << Fov << endl;
		}
		else
		{
			SetColour(15);
			cout << xorstr(" Fov = ") << Fov << endl;
		}
		if (M_Index == dist)
		{
			SetColour(10);
			cout << xorstr(" Distance aimbot= ") << Range << endl;
		}
		else
		{
			SetColour(15);
			cout << xorstr(" Distance aimbot= ") << Range << endl;
		}*/

		if ( M_Index == longneck )
			{
			SetColour ( 11 );
			cout << xorstr ( " LongNeck (MOUSE4) " ) << bools[LongNeck] << endl;
		}
		else
			{
			SetColour ( 13 );
			cout << xorstr ( " LongNeck (MOUSE4) " ) << bools[LongNeck] << endl;
		}

		//if (M_Index == One2)
		//{
		//	SetColour(10);
		//	cout << xorstr(" InfinityJump = ") << bools[InfinityJump] << endl;
		//}
		//else
		//{
		//	SetColour(15);
		//	cout << xorstr(" InfinityJump = ") << bools[InfinityJump] << endl;
		//}

		if (M_Index == ESP)
		{
			SetColour(11);
			cout << xorstr(" ESP ") << bools[RCS] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" ESP ") << bools[RCS] << endl;
		} 	
		if (M_Index == spider)
		{
			SetColour(11);
			cout << xorstr(" SpiderMan ") << bools[SpiderMan] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" SpiderMan ") << bools[SpiderMan] << endl;
		}
		
		if (M_Index == admin)
		{
			SetColour(11);
			cout << xorstr(" AdminMode ") << bools[FakeAdmin] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" AdminMode ") << bools[FakeAdmin] << endl;
		}

		//if (M_Index == One8)
		//{
		//	SetColour(10);
		//	cout << xorstr(" Fast Bullet = ") << bools[FastBullet] << endl;
		//}
		//else
		//{
		//	SetColour(15);
		//	cout << xorstr(" Fast Bullet = ") << bools[FastBullet] << endl;
		//}
		if (M_Index == thickbullet)
		{
			SetColour(11);
			cout << xorstr(" Thick Bullet ") << bools[BigBullet] << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" Thick Bullet ") << bools[BigBullet] << endl; //CustomFovBool
		}

		if (M_Index == cf)
		{
			SetColour(11);
			cout << xorstr(" Custom Fov ") << CustomFov << endl;
		}
		else
		{
			SetColour(13);
			cout << xorstr(" Custom Fov ") << CustomFov << endl;
		}

		//if (M_Index == One971)
		//{
		//	SetColour(10);
		//	cout << xorstr(" FlyHack(press F) = ") << bools[Flyhack] << endl;
		//}
		//else
		//{
		//	SetColour(15);
		//	cout << xorstr(" FlyHack(press F)   = ") << bools[Flyhack] << endl;
		//}

		//if (M_Index == One9711)
		//{
		//	SetColour(10);
		//	cout << xorstr(" LongHand = ") << bools[longhad] << endl;
		//}
		//else
		//{
		//	SetColour(15);
		//	cout << xorstr(" LongHand   = ") << bools[longhad] << endl;
		//}
		std::this_thread::sleep_for(100ms);
	}
}


void Overlay() {
	UpdateMenu();
	for (;;) {
		Navigation();
		if (updated == true)
		{
			updated = false;
			UpdateMenu();
		}
	}
}


BasePlayer* Fetch() {

	
	DWORD64 Id = LocalPlayer.BasePlayer->GetActiveWeapon()->GetItemID();
	if (Id == 1525520776 || Id == 200773292) return nullptr;
	static UINT64 oPlayerList = 0;
	if (!oPlayerList) {
		UINT64 val = safe_read(g_Base + 52895856, UINT64); // 293BF10 0x2940680 BasePlayer_c*
		UINT64 st = safe_read(val + 0xB8, UINT64);
		UINT64 list = safe_read(st + 0x10, UINT64);
		oPlayerList = safe_read(list + 0x28, UINT64);
	}																																							
	int EntityCount = safe_read(oPlayerList + 0x10, int);
	UINT64 EntityBuffer = safe_read(oPlayerList + 0x18, UINT64);
	for (int i = 0; i < EntityCount; i++) // int i = EntityCount-1; i >= EntityCount/4; i-- // int i = 0; i < EntityCount; i++
	{																			  	


		Player = (BasePlayer*)safe_read(EntityBuffer + 0x20 + (i * 0x8), UINT64);	  	

		if (Player || Player != LocalPlayer.BasePlayer || Player->IsValid()) continue;



		//if (lineesp) {
		//	Vector3 world_head = Player->GetBoneByID(BoneList::head);
		//	Vector2 screen_head = {};
		//	if (drawlerstarsxd == false) {
		//		if (LocalPlayer.WorldToScreen(world_head, screen_head))
		//		{
		//			/*printf("Игрок 0x%llX записан. Координаты: X: %d Y: %d\n", Player, (int)screen_head.x, (int)screen_head.y);*/
		//			player_list.push_back({ screen_head });
		//			drawlerstarsxd = true;
		//		}
		//	}
		//}
		if (VisibleCheck) {
			if (!Player->IsVisible()) continue;
		}
		if (IgnoreTeam) {
			UINT64 EntitySID = Player->GetSteamID();
			int size = LocalPlayer.BasePlayer->GetTeamSize();
			for (int j = 0; j < size; j++) {
				UINT64 SlotSID = LocalPlayer.BasePlayer->IsTeamMate(j);
				if (SlotSID == EntitySID) continue;
			}
		}
		if (AimFov(Player) <= Fov) {
			Vector3 pos = Player->GetPosition();
			float dist = Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetPosition(), pos);
			if (dist && dist <= Range) {
				printf("returning player 0x%llX to aimbot\n", Player);
				return Player;

			}
		}
	}
	return nullptr;



				

}

BasePlayer* Player1;

string WebString(string URL) {
	HINTERNET interwebs = InternetOpenA(xorstr("Mozilla/5.0"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = replaceAll(rtn, xorstr("|n"), xorstr("\r\n"));
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = replaceAll(rtn, xorstr("|n"), xorstr("\r\n"));
	return p;
}
#include <iostream>	
#include <fstream>	
//#include "DirectOverlay.h"


bool CheckedFile(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

string hrequest(string site, string param)
{
	HINTERNET hInternet = InternetOpenW(_(L"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.212 YaBrowser/21.5.2.638 Yowser/2.5 Safari/537.36"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (hInternet == NULL)
	{
		return xorstr("InternetOpenW failed(hInternet): ") + GetLastError();
	}
	else
	{
		wstring widestr;
		for (int i = 0; i < site.length(); ++i)
		{
			widestr += wchar_t(site[i]);
		}
		const wchar_t* site_name = widestr.c_str();

		wstring widestr2;
		for (int i = 0; i < param.length(); ++i)
		{
			widestr2 += wchar_t(param[i]);
		}
		const wchar_t* site_param = widestr2.c_str();



		HINTERNET hConnect = InternetConnectW(hInternet, site_name, 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

		if (hConnect == NULL)
		{
			return xorstr("InternetConnectW failed(hConnect == NULL): ") + GetLastError();
		}
		else
		{
			const wchar_t* parrAcceptTypes[] = { L"text/*", NULL };

			HINTERNET hRequest = HttpOpenRequestW(hConnect, L"GET", site_param, NULL, NULL, parrAcceptTypes, 0, 0);

			if (hRequest == NULL)
			{
				return xorstr("HttpOpenRequestW failed(hRequest == NULL): ") + GetLastError();
			}
			else
			{
				BOOL bRequestSent = HttpSendRequestW(hRequest, NULL, 0, NULL, 0);

				if (!bRequestSent)
				{
					return xorstr("!bRequestSent    HttpSendRequestW failed with error code ") + GetLastError();
				}
				else
				{
					std::string strResponse;
					const int nBuffSize = 1024;
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0)
					{
						bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
						strResponse.append(buff, dwBytesRead);
					}
					return strResponse;
				}
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}
}



std::string uint64_to_string(UINT64 value) {
	std::ostringstream os;
	os << value;
	return os.str();
}


void main(BasePlayer* BP, BasePlayer* LP, bool npc = false)
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	setlocale(LC_ALL, xorstr("Russian")); // Использование русских символов в проекте
	system(xorstr("cls"));
	//SetConsoleTitleA(xorstr("SCHEAT-PRO DEAD | ===> HyperCollision <=== "));
	//system(" start  https://discord.com/invite/3NuntFzksF ");

	//J();
	try {
		////	J();
		driver::initialize();
		g_Locked = false;
		g_Sock = driver::connect();
		if (g_Sock == INVALID_SOCKET)
		{
			MessageBox(NULL, L"Driver Not Loaded", L"Error", MB_OK);

			;
			cin.get();
			return;
		}
	}
	catch (...) {
		cin.get();
		return;
	}
	g_PID = RPid();

	u_Base = driver::get_process_base_address(g_Sock, g_PID, 0); //0 - UnityPlayer.dll, 
	g_Base = driver::get_process_base_address(g_Sock, g_PID, 1); //1 - GameAssembly.dll

	if (u_Base == 0 || g_Base == 0)
	{

		cin.get();
		return;
	}
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay, 0, 0, 0);
	EntityZaLoop();
	MainLoop();
	//	J();
}

#include <xstring>


struct monostr
	{
	char buffer[128];
	};
std::string readchar ( uintptr_t addr ) {
	std::string str = safe_read ( addr, monostr ).buffer;
	return str;
	}
void EntityZaLoop()
{
	//long long i = 0;
	//UINT64  ObjMgr1 = safe_read(u_Base + oGameObjectManager, UINT64);
	//UINT64 ObjMgr = safe_read(ObjMgr1, UINT64);
	//if (!ObjMgr) return;
	//UINT64 end = safe_read(ObjMgr, UINT64);
	//bool LP_isValid = false;
	//for (UINT64 Obj = safe_read(ObjMgr + 0x8, UINT64); (Obj && (Obj != end)); Obj = safe_read(Obj + 0x8, UINT64))
	//{
	//	UINT64 GameObject = safe_read(Obj + 0x10, UINT64);
	//	WORD Tag = safe_read(GameObject + 0x54, WORD);

	//	if (Tag == 6)
	//	{
	//		UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
	//		UINT64 Entity = safe_read(ObjClass + 0x18, UINT64);

	//		BasePlayer* Player = (BasePlayer*)safe_read(Entity + 0x28, UINT64);

	//		ESP = Player;
	//		
	//		if (safe_read(safe_read(GameObject + 0x60, UINT64), UINT64) == 0x616C506C61636F4C)
	//		{
	//			LP_isValid = true;
	//			LocalPlayer.BasePlayer = Player;
	//			firstentry = Obj;
	//			if (TodCycle && LocalPlayer.pViewMatrix)
	//				return;
	//		}
	//	}
	//	else if (Tag == 5) {
	//		UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
	//		UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
	//		LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0xDC);
	//	}
	//	else if (Tag == 20011) {
	//		UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
	//		UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
	//		UINT64 Dome = safe_read(Entity + 0x28, UINT64);
	//		TodCycle = safe_read(Dome + 0x38, UINT64);
	//	}
	//NextEnt:
	//	continue;
	//}
	//if (!TodCycle || !LP_isValid || LocalPlayer.BasePlayer->IsMenu()) {
	//	std::cin.get();
	//	return;
	//}

	bool LP_isValid = false;
	BasePlayer* AimEntity = 0;
	const auto camera_manager_offset = driver::read<uintptr_t> ( g_Sock, g_PID, u_Base + 0x1762E80 ); //  0x1762E80  0x1970400
	const auto camera_manager = driver::read<uintptr_t> ( g_Sock, g_PID, camera_manager_offset );
	const auto camera = driver::read<uintptr_t> ( g_Sock, g_PID, camera_manager );
	const auto camera_object = driver::read<uintptr_t> ( g_Sock, g_PID, camera + 0x30 );
	if ( !camera_object )
		return;
	const auto object_class = driver::read<uintptr_t> ( g_Sock, g_PID, camera_object + 0x30 );
	if ( !object_class )
		return;
	const auto Entity = driver::read<uintptr_t> ( g_Sock, g_PID, object_class + 0x18 );
	if ( !Entity )
		return;

	LocalPlayer.pViewMatrix = safe_read(Entity + 0x2E4 , Matrix4x4*);



	uintptr_t BaseNetworkable = safe_read ( g_Base + 52889792, uintptr_t ); // BaseEntity_c*
	uintptr_t h1 = safe_read ( BaseNetworkable + 0xB8, uintptr_t );
	uintptr_t h2 = safe_read ( h1 + 0x10, uintptr_t ); // 0x40
    if (!h2 )
    h2 = safe_read( h1  + 0x40,uintptr_t );
	uintptr_t h3 = safe_read ( h2 + 0x10, uintptr_t );
	uintptr_t h4 = safe_read ( h3 + 0x28, uintptr_t );
	auto objectList = safe_read ( h4 + 0x18, uintptr_t );
	auto objectListSize = safe_read ( h4 + 0x10, uint32_t );
	if ( !objectListSize )
		return;

	for ( int i = 0; i < objectListSize; i++ ) {

		uintptr_t Entity = safe_read ( objectList + 0x20 + (i * 0x8), uintptr_t ); if ( Entity <= 100000 ) continue;
		uintptr_t Object = safe_read ( Entity + 0x10, uintptr_t ); if ( Object <= 100000 ) continue;
		uintptr_t ObjectClass = safe_read ( Object + 0x30, uintptr_t ); if ( ObjectClass <= 100000 ) continue;
		pUncStr name = safe_read ( ObjectClass + 0x60, pUncStr ); if ( !name ) continue;
		std::string objectname = readchar ( ( uintptr_t)name );

		if ( (objectname.find ( _ ( "Local" ) ) != std::string::npos) ) 
{
			BasePlayer* Player = safe_read ( Object + 0x28, BasePlayer* );
			if ( !safe_read ( (uintptr_t)Player + 0x58 , uintptr_t) || safe_read( (uintptr_t)Player + 0x18, bool ) || !safe_read ( (uintptr_t)Player + O::BasePlayer::playerModel, uintptr_t ) ) continue;
			//if (!safe_read(Player + playermodel)) continue;
			if ( Player != LocalPlayer.BasePlayer ) {}
			LocalPlayer.BasePlayer = Player;
			LP_isValid = true;
}
	//	else if  (objectname.find ( _ ( "player.prefab" ) ) != std::string::npos)
	//		{
	//		BasePlayer* Players = (BasePlayer*)safe_read ( Object + 0x28 , DWORD64 ); //public ulong playerID;
	//		if ( !safe_read ( (const uintptr_t)Player + O::BasePlayer::playerModel, DWORD64 ) ) continue;
	//		if ( !Player->IsValid ( ) ) continue;
	//															Player = Players;
	//			 }

	// 
	//}

}

}




void MainLoop() {

	int last = -1;
	while (true) {
		//Fetch();
		Misc();
		if (GetAsyncKeyState(0x02)) {
			Aim(Player);
		}
		if (RPidSuccess == false) {
			RPid();
		}
		if (LocalPlayer.BasePlayer->IsDead()) {
			last = 0;
			continue;
		}
		int WeaponId = 0;
		WeaponData* active = LocalPlayer.BasePlayer->GetActiveWeapon();
		if (last && last != active->GetUID() && active->GetUID() != 0)
		{
			if (WeaponId != active->GetItemID())
			{
				WeaponId = active->GetItemID();
			}

			last = active->GetUID();
			if (last)
			{
				WeaponFix(active);
			}
		}
		else if (!last)
			last = active->GetUID();
	}
}

DWORD RPid() {
	if (g_PID) {
		if (!safe_read(g_Base, int)) {
			exit(1);
		}
		return g_PID;
	}
	else {
		DWORD pid = GetPID(L"RustClient.exe");
		
		if (!pid) {
			exit(1);
		}
		RPidSuccess = true;
		return pid;
	}
}

DWORD GetPID(const std::wstring& procname)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!procname.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!procname.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}
	CloseHandle(processesSnapshot);
	return 0;
}





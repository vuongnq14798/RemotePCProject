#include "pch.h"
#include "Util.h"
Util::Util(void) {}


Util::~Util(void) {}

CString Util::GetHostName()
{
	WSADATA wsadata;
	CString sHostName;

	if (!WSAStartup(0x202, &wsadata))
	{
		char szHostName[128] = { 0, };

		gethostname(szHostName, 128);

		CStringA saHostName = szHostName;
		sHostName = saHostName;

		WSACleanup();
	}

	return sHostName;
}

BOOL Util::GetScreenResolution(int& width, int& height)
{
	HDC hScreenDC = GetDC(NULL);
	width = GetDeviceCaps(hScreenDC, HORZRES);
	height = GetDeviceCaps(hScreenDC, VERTRES);
	DeleteDC(hScreenDC);
	return true;
}

void Util::PrintfByteArray(unsigned char* buff, int buflen)
{
	CString strLog = _T("");
	for (int i = 0; i < buflen; i++)
		strLog.Format(_T("%s %d"), strLog, (int)buff[i]);
}
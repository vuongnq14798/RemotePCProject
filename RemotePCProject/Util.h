#pragma once
class Util
{
public:
	Util(void);
	~Util(void);

	static CString GetHostName();
	static BOOL GetScreenResolution(int& width, int& height);
	static void PrintfByteArray(unsigned char* buff, int buflen);
};
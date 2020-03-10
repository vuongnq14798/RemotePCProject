#include "pch.h"
#include "RemotePC.h"
#include "Defines.h"

CRemotePC::CRemotePC(void)
{
}


CRemotePC::~CRemotePC(void)
{
}

void CRemotePC::StartProgram(char* ipaddr, int port)
{
	BOOL ret = FALSE;
	//main socket
	if (!CSocketController::GetInstance())
		return;
	CSocketController::GetInstance()->StartSocketController(ipaddr, port);
}

void CRemotePC::StopProgram()
{
	CSocketController::GetInstance()->StopSocketController();
}
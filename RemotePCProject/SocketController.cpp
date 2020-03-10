#include "pch.h"
#include <string>
#include "Defines.h"
#include "SocketController.h"

CSocketController* __pSocketController = NULL;

CSocketController::CSocketController(void)
{
	__tcpMainServerSocket = new TCPSocketBase();
	__tcpMainServerConnected = FALSE;
}


CSocketController::~CSocketController(void)
{
	SAFE_DELETE(__tcpMainServerSocket);
}

CSocketController* CSocketController::GetInstance()
{
	if (__pSocketController == NULL)
		__pSocketController = new CSocketController();
	return __pSocketController;
}

BOOL CSocketController::StartMainControl(char* ipaddr, int port)
{
	int err = __tcpMainServerSocket->connectSocket(ipaddr, port);
	return err;
}

void CSocketController::StopMainControl()
{
	if (__tcpMainServerSocket)
		__tcpMainServerSocket->closeSocket();
}

void CSocketController::StartSocketController(char* ipaddr, int port)
{
	int ret = 0;
	ret = StartMainControl(ipaddr, port);
}

void CSocketController::StopSocketController()
{
	StopMainControl();
}
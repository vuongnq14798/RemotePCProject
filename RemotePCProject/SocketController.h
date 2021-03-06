#pragma once
#include "Defines.h"
#include "ErrorCodes.h"
#include "TCPSocketBase.h"

class CSocketController
{
public:
	CSocketController(void);
	~CSocketController(void);

	static CSocketController* GetInstance();

	void StartSocketController(char* ipaddr, int port);
	void StopSocketController();

	BOOL StartMainControl(char* ipaddr, int port);
	void StopMainControl();
private:
	TCPSocketBase* __tcpMainServerSocket;
	BOOL			__tcpMainServerConnected;
};
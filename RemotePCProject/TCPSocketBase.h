#pragma once
#include "WS2tcpip.h"

class TCPSocketBase
{
public:
	TCPSocketBase();
	~TCPSocketBase();

	int 	closeSocket();
	int		connectSocket(char* ipaddr, int port, bool isAsync = true);
	int		sendSocket(char* buf, int len);
protected:
	static UINT connectThreadMain(void* arg);
	static UINT receiveThreadMain(void* arg);

	int connectInnerFunc(bool isAsync = true);
	void receiveThreadLoop(void);
	int receiveData(char* buf);
	int connectAsServer(void);


private:
	int _sockFd, _clientFd;
	CWinThread* _receiveLoop;
	CWinThread* _connectLoop;

	int _port, _buffLen;
	bool _isSocketConnected, _isSocketCreated,
		_isReceiveThreadRunning, _isConnectThreadRunning;
	bool _isServer;
	struct sockaddr_storage _theirAddr;
	struct sockaddr_in _servAddr;

	char _serverIp[INET6_ADDRSTRLEN];

	socklen_t sin_size;
};
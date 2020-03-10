#include "pch.h"
#include "TCPSocketBase.h"
#include "ErrorCodes.h"
#include "Defines.h"
#define LOG_TAG "TCPSocketBase"
#define LOCAL_IP_ADDR "127.0.0.1"

#define BACKLOG				10 
#define MAX_PACKET_SIZE 4096
TCPSocketBase::TCPSocketBase()
{
	_isSocketConnected = false;
	_isSocketCreated = false;
	_isReceiveThreadRunning = false;
	_isConnectThreadRunning = false;

	_receiveLoop = NULL;
	_connectLoop = NULL;
	_sockFd = NULL;
	_clientFd = NULL;
	_buffLen = NULL;
	_isServer = NULL;
	_port = NULL;
	sin_size = NULL;
}

TCPSocketBase::~TCPSocketBase()
{
}

int TCPSocketBase::connectSocket(char* ipaddr, int port, bool isAsync)
{
	int err = 0;
	WSADATA wsaData;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0)
	{
		return ERROR_UNKNOWN;
	}

	if (_isSocketCreated == false)
	{
		_isSocketCreated = true;
		if (ipaddr) strcpy(_serverIp, ipaddr);
		_port = port;
		_connectLoop = AfxBeginThread(connectThreadMain, (void*)this);
	}
	else
	{
		return ERROR_SOCKET_ALREADY_CREATED;
	}

}

UINT TCPSocketBase::connectThreadMain(void* arg)
{
	TCPSocketBase* h = reinterpret_cast<TCPSocketBase*>(arg);
	int ret = h->connectInnerFunc(true);

	if (ret != OK)
	{
		h->_isSocketCreated = false;
	}
	return 0;
}

int TCPSocketBase::connectInnerFunc(bool isAsync)
{
	_sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sockFd < 0)
	{
		return ERROR_SOCKET_CANT_OPEN;
	}
	int opt = 1;

	if (setsockopt(_sockFd, SOL_SOCKET, (SO_REUSEADDR), (char*)&opt, sizeof(int)) == -1)
	{
		return ERROR_SOCKET_CANT_SET_OPT;
	}

	int len, trysize, gotsize;
	len = sizeof(int);

	trysize = 512 * 1024;

	int err = setsockopt(_sockFd, SOL_SOCKET, SO_SNDBUF, (char*)&trysize, sizeof(int));
	if (err < 0)
	{

	}

	err = setsockopt(_sockFd, SOL_SOCKET, SO_RCVBUF, (char*)&trysize, sizeof(int));
	if (err < 0)
	{

	}
	return connectAsServer();
}

UINT TCPSocketBase::receiveThreadMain(void* arg)
{
	TCPSocketBase* h = reinterpret_cast<TCPSocketBase*>(arg);
	h->receiveThreadLoop();
	return 0;
}

void TCPSocketBase::receiveThreadLoop()
{
	_isReceiveThreadRunning = true;
	char* buf = new char[MAX_PACKET_SIZE];
	int res = 0;
	while (_isReceiveThreadRunning)
	{
		res = receiveData(buf);
		if (res < 0) break;
	}
	SAFE_DELETE_ARRAY(buf);
	_isReceiveThreadRunning = false;
	return;
}

int TCPSocketBase::receiveData(char* buf)
{
	UINT numbytes = 0;
	UINT read_max_bytes = MAX_PACKET_SIZE;

	numbytes = recv(_clientFd, buf, read_max_bytes, 0);

	if (numbytes == -1)
	{
		_isSocketConnected = false;
		return ERROR_RECV_FAILED;
	}
	else if (numbytes > 0)
	{
		/*if (_pOwner)
			_pOwner->TCP_ReceiveData(this, buf, numbytes);*/
		return OK;
	}
	else
	{
		return ERROR_SOCKET_CLOSED;
	}
	return OK;
}

int TCPSocketBase::connectAsServer(void)
{
	if (strlen(_serverIp) == 0) sprintf(_serverIp, "%s", LOCAL_IP_ADDR);

	memset((char*)&_servAddr, 0, sizeof(_servAddr));
	_servAddr.sin_family = PF_INET;
	_servAddr.sin_addr.s_addr = INADDR_ANY;
	_servAddr.sin_port = htons(_port);

	int ret = bind(_sockFd, (struct sockaddr*) & _servAddr, sizeof(_servAddr));
	if (ret < 0)
	{
		return ERROR_CANNOT_BIND_SOCKET;
	}
	if (listen(_sockFd, BACKLOG) == -1)
	{
		return ERROR_CANNOT_LISTEN_SOCKET;
	}

	sin_size = sizeof _theirAddr;

	_isConnectThreadRunning = TRUE;

	while (_isConnectThreadRunning)
	{
		_clientFd = accept(_sockFd, (struct sockaddr*) & _theirAddr, &sin_size);

		if (_clientFd == SOCKET_ERROR)
		{
			return ERROR_CANNOT_ACCEPT_CLIENT_SOCKET;
		}
		else
		{
			_receiveLoop = AfxBeginThread(receiveThreadMain, (void*)this);
			_isSocketConnected = TRUE;
		}
	}
	_isConnectThreadRunning = FALSE;
	return OK;
}

int TCPSocketBase::closeSocket()
{

	_isSocketCreated = false;
	if (_isServer)
	{
		shutdown(_clientFd, SD_BOTH);
		closesocket(_clientFd);
	}
	else
	{
		shutdown(_sockFd, SD_BOTH);
		closesocket(_sockFd);
	}

	_isSocketConnected = false;

	if (_isReceiveThreadRunning)
	{
		_isReceiveThreadRunning = false;
		DWORD dwRet = WaitForSingleObject(_receiveLoop->m_hThread, 2000);
		if (dwRet != WAIT_OBJECT_0 && dwRet != WAIT_FAILED) {
			TerminateThread(_receiveLoop->m_hThread, 0);
		}
	}
	return OK;
}

int TCPSocketBase::sendSocket(char* buf, int len)
{
	if (_isServer)
	{
		return send(_clientFd, (const char*)buf, len, 0);
	}
	else
	{
		return send(_sockFd, (const char*)buf, len, 0);
	}
}
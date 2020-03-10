#include "Util.h"
//#include "RecordScreen.h"
//#include "RecordAudio.h"
#include "SocketController.h"

//using namespace RemotePC;

class CRemotePC
{
public:
	CRemotePC(void);
	~CRemotePC(void);

	void StartProgram(char* ipaddr, int port);
	void StopProgram();
};
#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <Winbase.h>

#define PORT_TCP 6668
#define PORT_UDP 6667
#define DPEX_MAX_BUFFERSIZE 256

#define TIMEOUT 5000

struct DataPacket
{
	UCHAR id;
	int x;
	int y;
	int z;								//this will be used to store system message values
};

struct DataPacketEx
{
	UCHAR id;
	int	 bSize;							//the size of the used buffer portion
	int  reserved;						//reserved for send operations
	int  dpx_flag;						//reserved for system message handling
	char buffer[DPEX_MAX_BUFFERSIZE];
};

class XClient
{
public:
	XClient();
	XClient(UINT ID);
	XClient(IN_ADDR* addr);

	~XClient();

	SOCKET socketTCP;
	char* bufferTCP;

	UINT id;
	UINT room;
	sockaddr_in addressTCP;
	sockaddr_in addressUDP;
	

	int connectTo();
	int acceptFrom(SOCKET *listener);
	void sendTcpMessage(const DataPacket *packet);
	void sendUdpMessage(SOCKET &scoketUDP, const DataPacket *packet);
	void setID(UINT iId = 0);
	void setAddress(IN_ADDR* addr);
	void isTimedOut();
	void disconnect();
	char* getIp();
	static void idToAddr(UINT iID, IN_ADDR* addr);
	static UINT addrToId(const IN_ADDR* addr);

private:
	void setup();
	BOOL firstTry;
	UINT elapsedTime;
	int addrLen;
	int packetSize;

};
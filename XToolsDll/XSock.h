#pragma once
#pragma comment(lib, "ws2_32.lib")

//XSocket Version 1.55
#include <winsock2.h>
#include "XClient.h"
#include <vector>
//#define SELFCONNECT 1

#define MAX_CLIENTS 32
#define BACKLOG 32
#define ID_SYSMEX	255
#define SYS_JOINROOM  1
#define SYS_EXTENDED  2
#define SYS_AUTOCONN  3
#define JOIN_REQUEST  4
#define JOIN_RESPONSE 5

struct SecureClient
{
	in_addr address;
	bool isMaster;
	char name[256];
};

using namespace std;
typedef vector<SecureClient> SecureClientVector;

class XClient;
class XSock
{
public: 
	XSock();
	~XSock();

	void connect();
	void disconnect();
	void getClientsState();
	void join(UINT nRoom);
	void leave();
	void getClientList(in_addr* addrlist, unsigned int* roomlist, size_t* listSize);

	void insertAutorizedClient(char* ip, char* name, bool isMaster);

protected:
	UINT id;						//Ip address coded as an UINT

	void sendTcpMessageEx(DataPacketEx* data, int bufferSize);
	void sendTcpMessage(const DataPacket* data);
	void sendUdpMessage(const DataPacket* data);
	void sendTcpRoomMessageEx(DataPacketEx* data, int bufferSize);
	void sendTcpRoomMessage(const DataPacket* data);
	void sendUdpRoomMessage(const DataPacket* data);
	void insertIp(IN_ADDR* addr);
	void insertIp(UINT rID);
	bool isAutorized(SecureClient* owner = 0);
	bool isMaster(SecureClient* owner = 0);
	UINT getClientNum();

	virtual void procTcpMessageEx(const DataPacketEx* data, const in_addr* sender) = 0;
	virtual void procTcpMessage(const DataPacket* data,		const in_addr* sender) = 0;
	virtual void procUdpMessage(const DataPacket* data,		const in_addr* sender) = 0;
	virtual void logMessage(char *message, ... );

private:
	SOCKET listeningTCP;
	SOCKET socketUDP;
	sockaddr_in serverAddrTCP;		//To setup the listening socket TCP
	sockaddr_in serverAddrUDP;		//To setup the listening socket UDP
	sockaddr_in msgSender;			//To store information about the message sender
	hostent* phe;					//To get the machine ip list TODO: errore se ne ritorna + di 1 interfaccia
	int addrLen;
	timeval timeout;				//Timeout for select
	fd_set input_set;				//to check the readability
	fd_set serv_set;
	fd_set exc_set;					//to check winsock exceptions
	int nfds;						//Added for compatibility not needed!
	ULONG lMsg;						//for ioctlsocket
	DataPacket   *packetTcp;				
	DataPacket   *packetUdp;
	DataPacketEx *packetExTcp;		//To receive Extended length TCP packets
	DataPacketEx *packetExUdp;		//To receive Extended length UDP packets (STILL UNUSED)
	XClient* client[MAX_CLIENTS];	//Connected clients pointer array
	XClient* pending[MAX_CLIENTS];	//Pending clients pointer array
	XClient* ipList[MAX_CLIENTS];
	SecureClientVector autorizedClients;
	UINT cIndex;
	UINT ipIndex;
	UINT clientNum;
	UINT pendingNum;
	UINT room;
	int packetSize;
	int packetSizeEx;				//is the same of packetSize (provided for future developments)
	int res;
	bool connected;
	bool started;
	
	void startup();
	void checkOutConn();
	void checkInConn();
	void getMessages();
	void disconnect(UINT index);

	void sysProcTcpMessage(int index);	//System messages handler (variable length packets, client forwarding, room system)
	void forwardClient(UINT index);
	void connectToRecvAddr(UINT rID);
	void buildpacketEx(UINT index);
	void putClientInRoom(UINT index, DataPacket* data);
	void sendRoom(UINT index);
	
	bool getLocalIp();

	void rebuildFDs();
	void optimizeArray(XClient *array[]);
	int getLastClientIndx(XClient *array[]);
	int getFreeIndex(XClient *array[]);
};

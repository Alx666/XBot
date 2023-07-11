#include "XClient.h"
#include <stdio.h>
#include <stdlib.h>

XClient::XClient()
{
	setup();
	id = 0;
	room = 0;
}

XClient::XClient(UINT ID)
{
	setup();
	
	id = ID;
	addressTCP.sin_family = AF_INET;
	addressTCP.sin_port = htons(PORT_TCP);
	addressTCP.sin_addr.S_un.S_addr = ID;

	addressUDP = addressTCP;
	addressUDP.sin_port = htons(PORT_UDP);
}

XClient::XClient(IN_ADDR* addr)
{
	setup();
	id = XClient::addrToId(addr);
	addressTCP.sin_family = AF_INET;
	addressTCP.sin_port = htons(PORT_TCP);
	addressTCP.sin_addr.S_un.S_addr = id;

	addressUDP = addressTCP;
	addressUDP.sin_port = htons(PORT_UDP);
}

void XClient::setup()
{	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	addrLen = sizeof(addressTCP);
	packetSize = sizeof(DataPacket);

	firstTry = false;
	elapsedTime = 0;

	bufferTCP = new char[packetSize];

	memset(bufferTCP, 0, sizeof(DataPacket));
	memset(&addressTCP, 0, sizeof(sockaddr_in));
	memset(&addressUDP, 0, sizeof(sockaddr_in));

	socketTCP  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	unsigned long block = 1;
	ioctlsocket(socketTCP, FIONBIO,&block); 
}

XClient::~XClient()
{
	closesocket(socketTCP);

	delete [] bufferTCP;

	WSACleanup();
}


//******************************Connection functions
int XClient::connectTo()
{
	if(!firstTry)
	{
		firstTry = true;
		elapsedTime = GetTickCount();
	}

	if((GetTickCount() - elapsedTime) > TIMEOUT )
	{
		return WSAETIMEDOUT;
	}

	if(connect(socketTCP, (SOCKADDR*)&addressTCP, sizeof(SOCKADDR)) == SOCKET_ERROR)
		return WSAGetLastError();
	else
	{
		return 0;
	}
}

int XClient::acceptFrom(SOCKET *listener)
{
	socketTCP = accept(*listener, (struct sockaddr *)&addressTCP, &addrLen);
	addressUDP = addressTCP;
	addressUDP.sin_port = htons(PORT_UDP);

	if(socketTCP == INVALID_SOCKET)
	{
		return INVALID_SOCKET;
	}
	else
	{
		setID();
		return socketTCP;
	}
}

void XClient::sendTcpMessage(const DataPacket *packet)
{
	send(socketTCP, (char*)packet, packetSize, 0);
}

void XClient::sendUdpMessage(SOCKET &socketUDP, const DataPacket *packet)
{
	sendto(socketUDP, (char*)packet, packetSize, 0, (sockaddr *)&addressUDP, addrLen);
}

void XClient::disconnect()
{
	closesocket(socketTCP);
}


//*****************************Other Shit
void XClient::setID(UINT sId)
{

	if(sId != 0)
	{
		id = sId;
		return;
	}
	
	UCHAR* ptr = (UCHAR*)&id;
	ptr[0] = addressTCP.sin_addr.S_un.S_un_b.s_b1;
	ptr[1] = addressTCP.sin_addr.S_un.S_un_b.s_b2;
	ptr[2] = addressTCP.sin_addr.S_un.S_un_b.s_b3;
	ptr[3] = addressTCP.sin_addr.S_un.S_un_b.s_b4;
}

void XClient::idToAddr(UINT iID, IN_ADDR* addr)
{
	UCHAR* ptr = (UCHAR*)&iID;
	addr->S_un.S_un_b.s_b1 = ptr[0];
	addr->S_un.S_un_b.s_b2 = ptr[1];
	addr->S_un.S_un_b.s_b3 = ptr[2];
	addr->S_un.S_un_b.s_b4 = ptr[3];
}

UINT XClient::addrToId(const IN_ADDR* addr)
{
	UINT result;

	//result = inet_addr(inet_ntoa(*addr));
	
	UCHAR* ptr = (UCHAR*)&result;
	ptr[0] = addr->S_un.S_un_b.s_b1;
	ptr[1] = addr->S_un.S_un_b.s_b2;
	ptr[2] = addr->S_un.S_un_b.s_b3;
	ptr[3] = addr->S_un.S_un_b.s_b4;

	return result;
}


void XClient::setAddress(IN_ADDR* addr)
{
	addressTCP.sin_family = AF_INET;
	addressTCP.sin_port = htons(PORT_TCP);
	addressTCP.sin_addr = *addr;

	addressUDP = addressTCP;
	addressUDP.sin_port = htons(PORT_UDP);
	addressUDP.sin_addr = *addr;

	id = XClient::addrToId(addr);
}

char* XClient::getIp()
{
	char *ClientIp = inet_ntoa(addressTCP.sin_addr);
	return ClientIp;
}
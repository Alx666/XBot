#include "XSock.h"
#include <stdio.h>
#include <iostream.h> //DEBUG
//#define XSOCK_DEBUG //Enable for debug txt logging

XSock::XSock()
{

#ifdef XSOCK_DEBUG
	FILE *logfile = fopen("XSock.txt", "w");
	fclose(logfile);
#endif

	started = false;
	connected = false;
	ipIndex = 0;
	res		= 0;
	room    = 0;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	addrLen = sizeof(SOCKADDR_IN);

	packetUdp = new DataPacket;
	packetTcp = new DataPacket;
	packetExTcp = new DataPacketEx;
	packetExUdp = new DataPacketEx;

	memset(packetUdp,   0, sizeof(DataPacket));
	memset(packetTcp,   0, sizeof(DataPacket));
	memset(packetExTcp, 0, sizeof(DataPacket));
	memset(packetExUdp, 0, sizeof(DataPacket));
	memset(ipList,   0, sizeof(ipList));
	memset(client,   0, sizeof(client));
	memset(pending,  0, sizeof(pending));
}

XSock::~XSock()
{
	disconnect();
	delete packetUdp;
	delete packetTcp;
	delete packetExTcp;
	delete packetExUdp;
}

//start the connection procedure
//******************************
void XSock::connect()
{
	if(!started)
		startup();

	if(!started)
	{
		logMessage("XSocket::connect: Error, startup failed!\n");
		return;
	}

	if(connected)
	{
		logMessage("XSocket: already connected!\n");
		return;
	}

	for(UINT i = 0; i < ipIndex; i++)
	{

#ifdef SELFCONNECT
		if(true)	//BYPASS THE CONDITION TO SELF CONNECT 
#else
		if(id != XClient::addrToId(&ipList[i]->addressTCP.sin_addr))
#endif
		{
			pending[pendingNum] = new XClient(ipList[i]->id);

			pendingNum++;

			char *ClientIp = inet_ntoa(ipList[i]->addressTCP.sin_addr);
			logMessage("XSocket: Trying to connect %s\n", ClientIp);
		}
	}
	connected = true;
}

//disconnect all and terminate the server
//***************************************
void XSock::disconnect()
{
	for(cIndex = 0; cIndex < MAX_CLIENTS; cIndex++)
	{
		if(client[cIndex] != 0)
		{
			client[cIndex]->disconnect();
			delete client[cIndex];
			client[cIndex] = 0;
		}

		if(pending[cIndex] != 0)
		{
			delete pending[cIndex];
			pending[cIndex] = 0;
		}
	}

	clientNum = 0;
	pendingNum = 0;
	id = 0;

	connected = false;
	started = false;

	closesocket(listeningTCP);
	closesocket(socketUDP);
	
	WSACleanup();

	logMessage("XSocket: Disconnected\n");
}

//Send via tcp a variable length message, buffersize is 
//the used number of elements in the DataPacketEx::buffer
//**************************************************
void XSock::sendTcpMessageEx(DataPacketEx* data, int bufferSize)
{
	data->reserved = data->id;
	data->id = ID_SYSMEX;
	data->dpx_flag = SYS_EXTENDED;
	data->bSize = bufferSize;

	for(UINT i = 0; i<clientNum; i++)
	{
		send(client[i]->socketTCP, (char*)data, packetSizeEx + bufferSize, 0);
	}
}

//Send via tcp a DataPacket
//**************************************************
void XSock::sendTcpMessage(const DataPacket* data)
{
	for(UINT i = 0; i<clientNum; i++)
	{
		client[i]->sendTcpMessage(data);
	}
}

//Send via udp a DataPacket
//**************************************************
void XSock::sendUdpMessage(const DataPacket* data)
{
	for(UINT i = 0; i<clientNum; i++)
	{
		client[i]->sendUdpMessage(socketUDP, data);
	}
}

//Send via tcp a variable length message, only to clients in the same room
//**************************************************
void XSock::sendTcpRoomMessageEx(DataPacketEx* data, int bufferSize)
{
	data->reserved = data->id;
	data->id = ID_SYSMEX;
	data->dpx_flag = SYS_EXTENDED;
	data->bSize = bufferSize;

	for(UINT i = 0; i<clientNum; i++)
	{
		if(client[i]->room != 0 && room == client[i]->room)
			send(client[i]->socketTCP, (char*)data, packetSizeEx + bufferSize, 0);
	}
}

//Send via tcp a DataPacket
//**************************************************
void XSock::sendTcpRoomMessage(const DataPacket* data)
{
	for(UINT i = 0; i<clientNum; i++)
	{
		if(client[i]->room != 0 && room == client[i]->room)
			client[i]->sendTcpMessage(data);
	}
}

//Send via udp a DataPacket
//**************************************************
void XSock::sendUdpRoomMessage(const DataPacket* data)
{
	for(UINT i = 0; i<clientNum; i++)
	{
		if(client[i]->room != 0 && room == client[i]->room)
			client[i]->sendUdpMessage(socketUDP, data);
	}
}

//Tryes to accept/complete connections, get incoming data and process it
//**********************************************************************
void  XSock::getClientsState()
{
	if(!connected)
		return;

	getMessages();

	if(clientNum < MAX_CLIENTS) //connection managment
	{
		checkInConn();

		if(pendingNum > 0)
			checkOutConn();
	}

}

//Insert an addr into the knowIpList
//**********************************
void XSock::insertIp(IN_ADDR* addr)
{
	if(ipIndex >= MAX_CLIENTS)
	{
		logMessage("XSocket: client limit reached, aborting...\n");
		return;
	}

	ipList[ipIndex] = new XClient(addr);
	ipIndex++;
}

//Insert an addr into the knowIpList
//**********************************
void XSock::insertIp(UINT rID)
{
	if(ipIndex >= MAX_CLIENTS)
	{
		logMessage("XSocket: client limit reached, aborting...\n");
		return;
	}

	ipList[ipIndex] = new XClient(rID);
	ipIndex++;
}


//Inizialize XSock and set in listening state
//*******************************************
void XSock::startup()
{
	if(connected)
	{
		logMessage("XSocket::startup: already connected\n");
		return;
	}

	memset(client,			0, sizeof(client));
	memset(pending,			0, sizeof(pending));
	memset(packetUdp,		0, sizeof(DataPacket));
	memset(packetTcp,		0, sizeof(DataPacket));
	memset(packetExTcp,		0, sizeof(DataPacketEx));
	memset(packetExUdp,		0, sizeof(DataPacketEx));
	memset(&serverAddrTCP,	0, sizeof(SOCKADDR_IN));
	memset(&serverAddrUDP,	0, sizeof(SOCKADDR_IN));
	memset(&msgSender,		0, sizeof(SOCKADDR_IN));

	cIndex     = 0;
	clientNum  = 0;
	pendingNum = 0;
	room	   = 0;

	packetSize   = sizeof(DataPacket);
	packetSizeEx = sizeof(DataPacketEx) - DPEX_MAX_BUFFERSIZE;

	WSADATA wsaData;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData))
		logMessage("XSocket::startup: Error while attempting to initialize WinSock\n");

	serverAddrTCP.sin_family = AF_INET;
	serverAddrTCP.sin_addr.s_addr = INADDR_ANY;
	serverAddrTCP.sin_port = htons(PORT_TCP);

	serverAddrUDP.sin_family = AF_INET;
	serverAddrUDP.sin_addr.s_addr = INADDR_ANY;
	serverAddrUDP.sin_port = htons(PORT_UDP);

	listeningTCP = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socketUDP = socket(AF_INET,  SOCK_DGRAM, IPPROTO_UDP);
	unsigned long block = 1;
	ioctlsocket(socketUDP, FIONBIO,&block); 


	if(SOCKET_ERROR == bind(listeningTCP, (SOCKADDR*)&serverAddrTCP, sizeof(serverAddrTCP)))
	{
		logMessage("XSocket::startup: Error %i, could not bind TCP socket...\n", WSAGetLastError());
		disconnect();
		return;
	}
	if(SOCKET_ERROR == listen(listeningTCP, BACKLOG))
	{
		logMessage("Socket::startup: Error %i, could not start listening...\n", WSAGetLastError());
		disconnect();
		return;
	}
	if(SOCKET_ERROR == bind(socketUDP, (SOCKADDR*)&serverAddrUDP, sizeof(serverAddrUDP)))
	{
		logMessage("XSocket::startup: Error %i, could not bind UDP socket...\n", WSAGetLastError());
		disconnect();
		return;
	}

	if(!getLocalIp())
	{
		logMessage("Socket::startup: Error, cannot determinate local Ip address");
		disconnect();
		return;
	}

	//logMessage("XSocket: startup completed, Ip:%s->Id:%u\n",  inet_ntoa(serverAddrTCP.sin_addr),id);
	logMessage("XSocket: startup completed, Ip:%s\n",  inet_ntoa(serverAddrTCP.sin_addr));
	started = true;
}

//Tryes to complete outgoing connections
//**************************************
void XSock::checkOutConn()
{
	for(UINT i = 0; i<pendingNum; i++)
	{
		//Comment this code to SELFCONNECT
#ifndef SELFCONNECT
		bool skip = false;
		for(UINT j = 0; j<clientNum; j++)//seek if the connection is already been completed from the other client
		{
			if(pending[i]->id == client[j]->id)
			{
				delete pending[i];
				pending[i] = 0;
				pendingNum--;
				optimizeArray(pending);
				skip = true;
			}
		}
		if(skip)
			continue;
#endif
		//SELFCONNECT END

		switch(pending[i]->connectTo())
		{
		//Critical errors
		case WSAECONNREFUSED:
		case WSAENETUNREACH:	
		case WSAETIMEDOUT:	//resolve critical errors	
			{
				//logMessage("XSock::checkOutConn: remote client timed out!\n"); //DEBUG
				delete pending[i];
				pending[i] = 0;
				pendingNum--;
				optimizeArray(pending);

			} break;

		//Common non blocking errors, connection can be still completed
		case WSAEWOULDBLOCK:	break; //get some other time
		case WSAEALREADY:		break;
		case WSAEINVAL:			break;

		//The connection has been resolved
		case 0:
		case WSAEISCONN:
			{
				int fIndex = getFreeIndex(client);

				pending[i]->setID();
				client[fIndex] = pending[i];
				pending[i] = 0;
				clientNum++;
				pendingNum--;
				optimizeArray(pending);
				logMessage("XSocket: %s connected!\n", inet_ntoa(client[fIndex]->addressTCP.sin_addr));
			} break;
		}
	}
}

//Tryes to complete incoming connections
//**************************************
void XSock::checkInConn()
{
begin: //TEMP
	FD_ZERO(&serv_set);
	FD_SET(listeningTCP, &serv_set);
	nfds = listeningTCP + 1;

	if(select(nfds, &serv_set, NULL, NULL, &timeout) > 0) //If there are some readable sockets ready...
	{
		cIndex = getFreeIndex(client);

		if(cIndex == -1) //TODO: una volta che il socket di ascolto e' chiuso bisogna restartare la classe x ricevere nuove connessioni in ingresso
		{
			logMessage("XSocket::checkInConn: connections full...\n");
			closesocket(listeningTCP);
			return;
		}

		client[cIndex] = new XClient();
		
		if(INVALID_SOCKET == client[cIndex]->acceptFrom(&listeningTCP))
		{
			logMessage("XSocket::checkInConn: error %i, unable to accept incoming connection\n", WSAGetLastError());
			delete client[cIndex];
			client[cIndex] = 0;
			return;
		}
		else
		{
			logMessage("XSocket: %s connected!\n", inet_ntoa(client[cIndex]->addressTCP.sin_addr));
			clientNum++;

			sendRoom(cIndex);
			forwardClient(cIndex);
			optimizeArray(client);
			goto begin;
		}
	}
}

//Get incoming messages and process them
//**************************************
void XSock::getMessages()
{
	rebuildFDs();

	while(!ioctlsocket(socketUDP, FIONREAD, &lMsg) && lMsg > 0)
	{
		lMsg = 0;

		if(recvfrom(socketUDP, (char*)packetUdp, packetSize, NULL, (SOCKADDR*)&msgSender, &addrLen) == SOCKET_ERROR)
		{
			int res = WSAGetLastError();
			switch(res)
			{
			case WSAEWOULDBLOCK: break; //do nothing nessage queque is probably empty
			default: logMessage("XSocket::getMessages: Error, recvfrom %i\n", res); break;
			}
		}
		else
			procUdpMessage(packetUdp, &msgSender.sin_addr);
	}

	if(select(nfds, &input_set, NULL, &exc_set, &timeout) > 0) // check if there are errors or data to process
	{
		// Look Through all the clients to see which one is giving error or data
		for (UINT i = 0; i < clientNum; i++)
		{
			if(FD_ISSET(client[i]->socketTCP, &exc_set)) // There was an Error?
			{
				logMessage("XSocket: Error, client %i exception, disconnecting...\n", i);
				disconnect(i);
			}

			if((FD_ISSET(client[i]->socketTCP, &input_set))) // Actual Data coming through?
			{
				sysProcTcpMessage(i);
			}
		}
	}
}

//Process TCP clients for system events
//*************************************
void XSock::sysProcTcpMessage(int index)
{
	if(client[index] == 0)
		return;

	res = recv(client[index]->socketTCP, client[index]->bufferTCP, packetSize, NULL);
	getpeername(client[index]->socketTCP, (sockaddr*)&msgSender, &addrLen);

	switch(res)
	{
	case SOCKET_ERROR:
		{
			res = WSAGetLastError();
			switch(res)
			{
			case 10035: return; //WSAWOULDBLOCK
			default:	logMessage("XSocket: client %s disconnected, possible crash\n", client[index]->getIp()); 
						disconnect(index);
						return;
			}
		}
		break;
	case 0:
		{
			logMessage("XSocket: client %s disconnected\n", client[index]->getIp());
			disconnect(index);

		}
		break;
	default:
		{
			packetTcp = (DataPacket*)client[index]->bufferTCP;

			switch(packetTcp->id) 
			{
			case ID_SYSMEX:	//if recognize a system packet process it otherwise send it to the virtual function
				{
					switch(packetTcp->z)
					{
					case SYS_EXTENDED: buildpacketEx(index);				 break;	//get the rest of the data and send to virtual func
					case SYS_AUTOCONN: connectToRecvAddr(packetTcp->x);		 break;
					case SYS_JOINROOM: putClientInRoom(index, packetTcp);	 break;
					}
				} 
				break;

			default: procTcpMessage(packetTcp, &msgSender.sin_addr);	break;
			}
		}
		break;

	}
	
}



//Disconnect client[index] and re-optimize the array
//**************************************************
void XSock::disconnect(UINT index)
{
	client[index]->disconnect();

	delete client[index];
	client[index] = 0;

	optimizeArray(client);
	clientNum--;
}

//Transmit client[index] ip tp all other clients
//**********************************************
void XSock::forwardClient(UINT index)
{
	if(clientNum <= 0)
		logMessage(" no peers found!\n");

	DataPacket data;
	data.id = ID_SYSMEX;
	data.z =  SYS_AUTOCONN;
	data.x = client[index]->id;

	for(UINT i = 0; i < clientNum; i++)
	{
		if(client[i] != 0 && (i != index)) //do not forward to the id sender
		{
			logMessage("XSocket: forwarding: sending %s to %s...\n", client[index]->getIp(), client[i]->getIp());
			client[i]->sendTcpMessage(&data);
		}
	}
}

//connect to a received Ip address
//********************************
void XSock::connectToRecvAddr(UINT rIp)
{
	if(clientNum >= MAX_CLIENTS)
		return;

	//first we seek the ID in the online clients
	for(UINT i = 0; i < clientNum; i++)
	{
		if(client[i]->id == rIp)
		{
			//logMessage("XSock::connectToRecvAddr: know id received...skipping\n"); //DEBUG
			return;
		}
	};

	//the if we have received our own ID, (should not!)
	if(rIp == id)
		return;

	logMessage("XSocket: Unknow ip received...trying connection\n");

	cIndex = getFreeIndex(pending);

	if(cIndex == -1)
	{
		logMessage("XSocket::connectToRecvAddr: pending queque full...\n");
		return;
	}
	
	pending[cIndex] = new XClient(rIp);
	pendingNum++;
}

//when an extended packet is detected this function get the rest of the data
//and sent the packetEx to the virtual processing function
//*************************************************************
void XSock::buildpacketEx(UINT index)
{
	memset(packetExTcp, 0, packetSizeEx + DPEX_MAX_BUFFERSIZE);
	memcpy(packetExTcp, packetTcp, packetSize);

	packetExTcp->id = packetExTcp->reserved;
					
	if(packetExTcp->bSize > 0)
		res = recv(client[index]->socketTCP, packetExTcp->buffer, packetExTcp->bSize, 0);

	procTcpMessageEx(packetExTcp, &msgSender.sin_addr);
}

//Retreive the local ip address
//*****************************
bool XSock::getLocalIp()
{
    char ac[80];
    if(gethostname(ac, sizeof(ac)) == SOCKET_ERROR) 
	{
		logMessage("XSock::getLocalIp: error getting the hostname\n");
		return false;
    }


    phe = gethostbyname(ac);


    if(phe == 0) 
	{
		logMessage("XSock::getLocalIp: error invalid phe\n");
		return false;
    }


	for(int i = 0; phe->h_addr_list[i] != 0; i++)
	{
		//counting the number o addresses found
	}

	if(i == 1)
	{
		memcpy(&serverAddrTCP.sin_addr, phe->h_addr_list[0], sizeof(struct in_addr));
		id = XClient::addrToId(&serverAddrTCP.sin_addr);
	}
	else
	{
		logMessage("XSock::getLocalIp: Error, multiple interfaces found!\n");
	}

	return true;
}

//Builds the FDSets to perform select functions
//*********************************************
void XSock::rebuildFDs()
{
	FD_ZERO(&input_set);
	FD_ZERO(&exc_set);
	nfds = 0;

	for (UINT i = 0; i < clientNum; i++)
	{
		FD_SET(client[i]->socketTCP, &input_set);
		FD_SET(client[i]->socketTCP, &exc_set);
		FD_SET(socketUDP, &input_set);
		nfds++;
	}
}

//Ordinate the clients in the first free positions
//***********************************************
void XSock::optimizeArray(XClient *array[])
{
	UINT clIndex, freeIndex;
	bool done = false;

	while(!done)
	{
		clIndex = getLastClientIndx(array);
		freeIndex = getFreeIndex(array);

		if(freeIndex > clIndex)
		{
			done = true;
		}
		else if(freeIndex != -1 && clIndex != -1) //non ci sono client da spostare (0 connessioni) oppure nn ci sono spazi liberi (tutto pieno)
		{
			array[freeIndex] = array[clIndex];
			array[clIndex] = 0;
		}
		else
		{
			done = true;
		}
	}
}


//Returns the index of the last client in the Array if present, -1 if not.
//************************************************************************
int XSock::getLastClientIndx(XClient *array[])
{
	for(int i = MAX_CLIENTS-1; i >= 0; i--)
	{
		if(array[i] != 0)
			return i;
	}

	return -1;
}

//Returns the index of the first free position found in the client Array -1 otherwise.
//************************************************************************************
int XSock::getFreeIndex(XClient *array[])
{
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(array[i] == 0)
		{
			return i;
		}
	}

	return -1;
}

//log Errors and shot screen output, files are open at every call to garant progressive logging during debug phases
//*****************************************************************************************************************
void XSock::logMessage(char *message, ... ) 
{
	char buffer[1024];
	va_list	args;

	if(NULL == message)		
		return;

	va_start( args, message );
	vsprintf( buffer, message, args );
	va_end( args );
	printf(buffer); //output used for console apps

#ifdef XSOCK_DEBUG
	FILE *logfile;



	logfile = fopen("XSock.txt", "a");
	if(logfile == NULL)
		return;

	fprintf(logfile, "%s", buffer);
	fclose(logfile);
#endif	
}

UINT XSock::getClientNum()
{
	return clientNum;
}


//								Room managment functions
//*****************************************************************************************
//*****************************************************************************************




//Join a room, and notify the event to all other clients
//******************************************************
void XSock::join(UINT nRoom)
{
	if(room != 0)
	{
		if(room == nRoom) //if trying to re-enter this room
		{
			logMessage("XSocket: already in room %i\n", room);
			return;
		}
		else
			leave();
	}

	memset(packetTcp, 0, packetSize);
	packetTcp->id = ID_SYSMEX;
	packetTcp->z  = SYS_JOINROOM;
	packetTcp->y  = JOIN_REQUEST;
	packetTcp->x  = nRoom;
	room = nRoom;

	sendTcpMessage(packetTcp);

	logMessage("XSocket: joined room %i\n", room);
}

//Leave the current room and notify it to all connected clients
//*************************************************************
void XSock::leave()
{
	if(room == 0)
	{
		logMessage("XSocket: cannot leave main room\n");
		return;
	}

	logMessage("XSocket: leaving room %i...\n", room);

	memset(packetTcp, 0, packetSize);
	packetTcp->id = ID_SYSMEX;
	packetTcp->z  = SYS_JOINROOM;
	packetTcp->y  = JOIN_REQUEST;
	packetTcp->x  = 0;
	room = 0;

	sendTcpMessage(packetTcp);
}

//Send to the index client the room we are in
//*******************************************
void XSock::sendRoom(UINT index)
{
	memset(packetTcp, 0, packetSize);
	packetTcp->id = ID_SYSMEX;
	packetTcp->z  = SYS_JOINROOM;
	packetTcp->y  = JOIN_RESPONSE;
	packetTcp->x  = room;

	send(client[index]->socketTCP, (char*)packetTcp, packetSize, 0);
}

//When a SYS_JOINROOM is received process the message here
//********************************************************
void XSock::putClientInRoom(UINT index, DataPacket* data)
{
	if(data->y == JOIN_REQUEST) // if calling client wants to join a room that's not main (room 0)
	{
		client[index]->room = data->x;	//we store the room he is entered

		if((room == client[index]->room) && (client[index]->room != 0))	//if we are in the same room we should tell him
		{
			sendRoom(index);
			logMessage("XSocket: client %s joined the room\n", client[index]->getIp());
		}

	}
	else if(data->y == JOIN_RESPONSE) //if we are getting infos from the other clients in the same room
	{
		client[index]->room = data->x; //a client is telling us in witch room he is
		logMessage("XSocket: client %s is in Room:%i\n", client[index]->getIp(), client[index]->room);
	}
}


//fill a buffer of XClients in_addr
//************************************************************
void XSock::getClientList(in_addr* addrlist, unsigned int* roomlist, size_t* listSize)
{
	SOCKADDR_IN temp;
	unsigned int i;
	unsigned long msg;

	for(i = 0; (i < clientNum) && (i < *listSize); i++)
	{
		memset(&temp, 0, sizeof(SOCKADDR_IN));

		getpeername(client[i]->socketTCP, (sockaddr*)&temp, &addrLen);

		roomlist[i] = client[i]->room;
		addrlist[i] = temp.sin_addr;
	}

	*listSize = clientNum;
}

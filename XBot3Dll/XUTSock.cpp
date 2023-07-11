#include "XUTSock.h"
#include "XBot.h"
#include <stdio.h>

XUTSock::XUTSock() : XSock()
{
	//memset(playerList,0,sizeof(XPlayer)*32);
	packetSize = sizeof(DataPacket);
	memset(&pkt, 0, packetSize);
}

XUTSock::~XUTSock()
{
	names.clear();
}


void XUTSock::procTcpMessageEx(const DataPacketEx* data, const in_addr* sender)
{
	switch(data->id)
	{
	case ID_STRING: processChatMessage(data, sender); break;
	case ID_KILL:	processKillUTInstance(data, sender); break;
	default: break;
	}
}

//Process clients data
void XUTSock::procTcpMessage(const DataPacket* data, const in_addr* sender)
{
	switch(data->id)
	{
	case ID_TRESET: processTimerOps(data->x); break;
	default: break;//invalid id received
	}
}

void XUTSock::procUdpMessage(const DataPacket* data, const in_addr* sender)
{	
	logMessage("Udp->ID:%i X:%i Y:%i Z:%i sender:%s\n",data->id,data->x,data->y,data->z,inet_ntoa(*sender));	
}

//log Errors and shot screen output, files are open at every call to garant progressive logging during debug phases
//*****************************************************************************************************************
void XUTSock::logMessage(char *message, ... ) 
{	


	
	char buffer[1024];
	FILE *logfile;
	va_list	args;

	if(NULL == message)		
		return;

	va_start( args, message );
	vsprintf( buffer, message, args );
	va_end( args );


	XBot* xbot = XBot::getXBot();

	if(buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = 0;//rimuove endline
	xbot->console->addHistoryLine(buffer , 0xFFFFFFFF);
	xbot->console->popUp();
	
}

void XUTSock::associateNameAndIp(UINT rID, char* name)
{
	names[rID] = name;

	insertIp(rID);
}

void XUTSock::loadConfig()
{

	XBot* xbot =  XBot::getXBot();

	int i = 0;
	while(i < MAX_PLAYERS && xbot->xconfig->playerlist[i].name != 0)
	{
		associateNameAndIp(xbot->xconfig->playerlist[i].codedIp, xbot->xconfig->playerlist[i].name);
		i++;
	}
	
	memcpy(playerList, xbot->xconfig->playerlist, sizeof(XPlayer)*32);
	
}


void XUTSock::sendTimerShieldReset()
{
	memset(&pkt, 0, packetSize);

	pkt.id = ID_TRESET;
	pkt.x = TIMER_SHIELD;
	sendTcpRoomMessage(&pkt);

}

void XUTSock::sendTimerRedeemReset()
{
	memset(&pkt, 0, packetSize);

	pkt.id = ID_TRESET;
	pkt.x = TIMER_REDEEM;
	sendTcpRoomMessage(&pkt);
}

void XUTSock::sendTimerDDamageReset()
{
	memset(&pkt, 0, packetSize);

	pkt.id = ID_TRESET;
	pkt.x = TIMER_DDAMAGE;
	sendTcpRoomMessage(&pkt);
}

//Send a message that will be displayed in the console to all the connected clients
void XUTSock::sendChatMessage(const char *buffer, int size)
{
	DataPacketEx message;
	memset(&message, 0, sizeof(message));

	message.id = ID_STRING;

	if(!size)
		message.bSize = strlen(buffer);
	else
		message.bSize = size;

	if(message.bSize > DPEX_MAX_BUFFERSIZE)
		return;

	strcpy(message.buffer, buffer);

	sendTcpMessageEx(&message, message.bSize);
}

void XUTSock::processTimerOps(UINT value)
{
	
	XBot* xbot = XBot::getXBot();

	switch(value)
	{
	case TIMER_SHIELD: xbot->resetShield100Timer();	break;
	case TIMER_DDAMAGE:xbot->resetDDamageTimer();	break;
	case TIMER_REDEEM: xbot->resetRedeemTimer();	break;
	}
	
}

void XUTSock::processChatMessage(const DataPacketEx* data, const in_addr* sender)
{
	PlayerNamesMap::iterator it;
	char* playerName;

	it = names.find(sender->S_un.S_addr);

	if(it == names.end())
	{
		playerName = inet_ntoa(*sender);
	}
	else
		playerName = it->second;
	
	XBot* xbot = XBot::getXBot();
	char buffer[1024];

	sprintf(buffer,"<%s>: %s", playerName, data->buffer);

	xbot->console->addHistoryLine(buffer , 0xFF00FFFF);
	xbot->console->popUp();
}


void XUTSock::printClientList()
{
	in_addr clientList[MAX_CLIENTS];
	UINT roomList[MAX_CLIENTS];

	UINT listsSize = MAX_CLIENTS;
	char* strAddr;


	memset(clientList, 0, MAX_CLIENTS * sizeof(in_addr));
	memset(roomList,   0, MAX_CLIENTS * sizeof(UINT));

	getClientList(clientList, roomList, &listsSize);

	logMessage("Ip\t\t\tRoom\n");
	for(UINT i = 0; i < listsSize; i++)
	{
		strAddr = inet_ntoa(clientList[i]);
		logMessage("%s\t\t%i\n",strAddr, roomList[i]);
	}
}

void XUTSock::sendKillUTInstance(char* TargetIp)
{
	DataPacketEx message;
	memset(&message, 0, sizeof(message));

	message.id = ID_KILL;
	message.bSize = strlen(TargetIp);

	if(message.bSize > DPEX_MAX_BUFFERSIZE)
	{
		logMessage("XSocket::sendKillUTInstance: invalid target address");
		return;
	}

	strcpy(message.buffer, TargetIp);

	sendTcpMessageEx(&message, message.bSize);
}

void XUTSock::processKillUTInstance(const DataPacketEx* data, const in_addr* sender)
{
	char* playerName = inet_ntoa(*sender);
	
	XBot* xbot = XBot::getXBot();
	char buffer[1024];

	UINT addr = inet_addr(data->buffer);


	if(addr == id)
	{
		//exit(1);
		xbot->console->addHistoryLine("XBot Term" , 0xFFF00000);
		xbot->console->popUp();

	}

}

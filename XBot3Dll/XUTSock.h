#pragma once

#include "XSock.h"
#include "..\\XBotLauncher\\XConfig.h"
#include <map>

//Packets Headers
#define ID_TRESET    1
#define ID_STRING	 2
#define ID_KILL		 3

//Packet X Values
#define TIMER_SHIELD   0
#define TIMER_DDAMAGE  1
#define TIMER_REDEEM   2

using namespace std;
class XUTSock : public XSock
{
	public:
		typedef map<int, char*> PlayerNamesMap;

		XUTSock();
		~XUTSock();

		void loadConfig();

		void sendTimerShieldReset();
		void sendTimerRedeemReset();
		void sendTimerDDamageReset();
		void sendChatMessage(const char *buffer, int size = 0);
		void sendKillUTInstance(char* TargetIp);

		void printClientList();

	private:
		PlayerNamesMap names;

		void associateNameAndIp(UINT rID, char* name);
		void logMessage(char *message, ... );
		void procTcpMessageEx(const DataPacketEx* data,	  const in_addr* sender);
		void procTcpMessage(const DataPacket* data,		  const in_addr* sender);
		void procUdpMessage(const DataPacket* data,		  const in_addr* sender);
		void processChatMessage(const DataPacketEx* data, const in_addr* sender);
		void processTimerOps(UINT value);
		void processKillUTInstance(const DataPacketEx* data, const in_addr* sender);

		DataPacket pkt;
		short packetSize;
		XPlayer playerList[32];
};
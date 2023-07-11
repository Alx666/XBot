#pragma once

#include "XCommandHandler.h"

class XUT2k4CommandHandler : public XCommandHandler
{

	public:
		XUT2k4CommandHandler() {buildCommandList();};

		void processParsedCommand(char* &result);
		void buildCommandList();

	private:

		char* onSetAlpha();
		char* onClrscr();
		char* onBkgrnd();
		char* onSetAutoBlastComboRange();
		char* onConnect();
		char* onDisconnect();
		char* onSetXHairSize();
		char* onSetPlayerSpeedMode();
		char* onSetUnlockStr();
		char* onSetAimSpeed();
		char* onEnableTimer();
		char* onEnableTimerSound();
		char* onAddToStartup();
		char* onSetImodeType();
		char* onSetWeaponRange();
		char* onJoin();
		char* onLeave();
		char* onGetPlayerList();
		char* onTeam();
		char* onEnableRadar();

		void onChatMessage();


		//SUPPORT
		unsigned int getWeaponCRCfromStrName(string* name);

};

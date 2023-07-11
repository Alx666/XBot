#pragma once

#include <string>
#include <d3dx8core.h>
#include <d3d8types.h>
#include "XUT2k4CommandHandler.h"

using namespace std;

#define CONSOLE_ANIMTIME			150.0f	
#define CONSOLE_TIMEOUT				2000.0f	
#define	CONSOLE_SIZEY				128
#define MAX_CONSOLE_TEXT_BUFFER		2000
#define DEFAULT_HISTORY_COLOR		D3DCOLOR_RGBA(255, 255, 0, 255)

class  XConsole
{

	public:
		XConsole();
		~XConsole() {delete commandHandler;};


		void setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef);
		void draw();
		void slideIn();
		void slideOut();
		void setViewport(int width, int height);
		void getKeyPress(WPARAM* wParam);
		void addHistoryLine(const char* str);
		void addHistoryLine(const char* str, D3DCOLOR color);
		void addSprintfLine(const char* str, ...);
		bool switchBkgrndMode();
		bool switchGetKeyPressMode();
		void setAlpha(char alpha);
		void clearScreen();
		void popUp(bool mode = true);


		bool getIsPopUpping()					{return isPopUpping;};
		bool getIsOut()							{return isOut;};
		bool acceptKeyInput()					{return getKeyPressSwitch;};
		bool getBkgrnMode()						{return backgroundSwitch;};		
		XCommandHandler* getCommandHandler()	{return commandHandler;}

	private:
		
		class consoleString : public string
		{
			public:
				consoleString():string()					{color = DEFAULT_HISTORY_COLOR;pixelHeight=0;}; 
				consoleString(string str):string(str)		{color = DEFAULT_HISTORY_COLOR;pixelHeight=0;}; 
				consoleString(const char* str):string(str)	{color = DEFAULT_HISTORY_COLOR;pixelHeight=0;}; 


				D3DCOLOR	color;
				int			pixelHeight;
		};

		typedef XConsole::consoleString consoleString;


		XCommandHandler*	commandHandler;
		
		bool	isOut;
		bool	slidingIn;
		bool	slidingOut;
		bool	backgroundSwitch;
		bool	getKeyPressSwitch;
		bool	isPopUpping;

		LPDIRECT3DDEVICE8	d3dDevice;
		ID3DXSprite*		spriteDrawer;
		IDirect3DTexture8*	console;
		RECT				consolePos;

		float			xOffset;
		float			yOffset;
		float			consoleTimeout;
		
		unsigned int	time;
		unsigned int	deltaTime;

		ID3DXFont*		consoleCurrentLineFont;
		ID3DXFont*		consoleHistoryFont;

		D3DCOLOR		consoleFontColor;
		D3DCOLOR		consoleColor;

		RECT			consoleFontPos;
		RECT			consoleCurrentLineFontPos;
		RECT			consoleHistoryFontPos;

		vector<consoleString>	consoleHistory;
		string					currentLineStr;
		string					lastLineStr;
		int						caretPos;
		int						consoleTextBufferHeight;
		int						pgUpShift;


		void			calculateYOffset();
		unsigned char	charFromVK(WPARAM vk, bool shift);
		void			autoCompleteLine();
		void			onReturnPress();



};		

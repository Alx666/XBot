#include "XBot.h"
#include "XConsole.h"


XConsole::XConsole()
{
	isOut				= false;
	slidingIn			= false;
	slidingOut			= false;
	backgroundSwitch	= false;
	getKeyPressSwitch	= true;
	isPopUpping			= false;


	d3dDevice		= NULL;
	spriteDrawer	= NULL;
	console			= NULL;

	xOffset		= 0;
	yOffset		= 0;
	time		= 0;
	deltaTime	= 0;
	consoleTimeout = CONSOLE_TIMEOUT;


	consoleCurrentLineFont	= 0;
	consoleHistoryFont		= 0;
	consoleFontColor		= D3DCOLOR_RGBA(255, 255, 255, 255);
	consoleColor			= D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0xBB);

	memset(&consoleFontPos, 0, sizeof(RECT));
	memset(&consoleCurrentLineFontPos, 0, sizeof(RECT));
	memset(&consolePos, 0, sizeof(RECT));
	memset(&consoleHistoryFontPos, 0, sizeof(RECT));


	consoleHistory.clear();
	currentLineStr.erase();
	currentLineStr.append(" ");
	lastLineStr.erase();
	lastLineStr.append(" ");

	caretPos = 0;
	consoleTextBufferHeight = 0;
	pgUpShift = 0;

	commandHandler = new XUT2k4CommandHandler();
}


void XConsole::draw()
{
	if (!isOut)
		return;

	calculateYOffset();

	spriteDrawer->Begin();
	spriteDrawer->Draw(console, NULL, NULL, NULL, 0, &D3DXVECTOR2(consolePos.left, consolePos.top + yOffset), consoleColor);
	spriteDrawer->End();
	
	if (!slidingOut && !slidingIn)
	{
		char str[512];
		str[0] = '[';
		str[1] = '>';
		str[2] = ' ';
		memcpy(&str[3],currentLineStr.c_str(),caretPos );
		str[caretPos + 3] = '&';
		memcpy(&str[caretPos + 4],&currentLineStr.c_str()[caretPos],(currentLineStr.size() - caretPos) + 1 );
		
		
		if(getKeyPressSwitch)
		{
			
			consoleCurrentLineFont->Begin();
			consoleCurrentLineFont->DrawText(str, -1, &consoleCurrentLineFontPos, DT_LEFT , consoleFontColor);
			consoleCurrentLineFont->End();
		}

		consoleHistoryFont->Begin();
		consoleHistoryFontPos.top = consoleHistoryFontPos.bottom + pgUpShift;
		for(int i = 0; i < consoleHistory.size(); i++)
		{
			consoleHistoryFontPos.top -= consoleHistory[i].pixelHeight;
			if(consoleHistoryFontPos.top < consoleHistoryFontPos.bottom && consoleHistoryFontPos.top > 0)
				consoleHistoryFont->DrawText(consoleHistory[i].c_str(), -1, &consoleHistoryFontPos, DT_LEFT | DT_EXPANDTABS | DT_EDITCONTROL | DT_WORDBREAK, consoleHistory[i].color);
		}
		consoleHistoryFont->End();
		
	}
}

void XConsole::setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef)
{
	XBot* xbot = XBot::getXBot();
	
	d3dDevice = d3dDeviceRef;
	D3DXCreateSprite(d3dDevice, &spriteDrawer);
	

	void* data;
	unsigned int fsize;
	
	fsize = xbot->xffReader->GetFile("XBot_console","bmp",&data);
	D3DXCreateTextureFromFileInMemoryEx(d3dDevice,data,fsize, 512, 128, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0xFF000000, NULL, NULL, &console);
	delete[] data;


	//Creazione dei font
	LOGFONT LogFont = {12, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Terminal"};
	D3DXCreateFontIndirect(d3dDevice, &LogFont, &consoleCurrentLineFont);	
	
	LOGFONT LogFont2 = {9, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Terminal"};
	D3DXCreateFontIndirect(d3dDevice, &LogFont2, &consoleHistoryFont);	


}

void XConsole::setViewport(int width, int height)
{
	consoleCurrentLineFontPos.left		= width/4 + 5;
	consoleCurrentLineFontPos.right		= consoleCurrentLineFontPos.left + (width/4)*2 - 10;
	consoleCurrentLineFontPos.top		= CONSOLE_SIZEY - 20;
	consoleCurrentLineFontPos.bottom	= height/6 - 5;
	
	consoleHistoryFontPos.left		= width/4 + 5;
	consoleHistoryFontPos.right		= consoleCurrentLineFontPos.left + (width/4)*2 - 10;
	consoleHistoryFontPos.top		= height/6 - 30;
	consoleHistoryFontPos.bottom	= height/6 - 30;


	consolePos.left		= width/4;
	consolePos.right	= (width/4)*2;
	consolePos.top		= -CONSOLE_SIZEY;
	consolePos.bottom	= 0;


}

void XConsole::slideOut()
{
	if(!isOut)
	{
		slidingOut = true;
		slidingIn = false;
		isOut = true;
		time = GetTickCount();
		getKeyPressSwitch = true;

	}
}
void XConsole::slideIn()
{
	backgroundSwitch = false;
	slidingIn = true;
	slidingOut = false;
	time = GetTickCount();

}

void XConsole::calculateYOffset()
{
	if(!isOut /*|| backgroundSwitch*/)
		return;
	
	deltaTime = GetTickCount() - time;

	if(isPopUpping && deltaTime > consoleTimeout)
	{
		slideIn();
		deltaTime = GetTickCount() - time;
	}

	if(slidingOut)
	{	

		if(deltaTime < CONSOLE_ANIMTIME)
		{
			yOffset = CONSOLE_SIZEY * (deltaTime/CONSOLE_ANIMTIME);
		}
		else
		{
			yOffset = (float)CONSOLE_SIZEY;
			slidingOut = false;
		}
	}
	else if(slidingIn)
	{

		if(deltaTime < CONSOLE_ANIMTIME)
		{
			yOffset = CONSOLE_SIZEY -(CONSOLE_SIZEY * (deltaTime/CONSOLE_ANIMTIME)); 
		}
		else
		{
			yOffset = 0.0f;
			slidingIn = false;
			isOut = false;
			isPopUpping = false;

		}
	}


}

bool XConsole::switchBkgrndMode()
{
	backgroundSwitch = !backgroundSwitch;
	
	if(!isOut)
		slideOut();

	if(backgroundSwitch)
		getKeyPressSwitch = false;
	else
		getKeyPressSwitch = true;
	
	
	return backgroundSwitch;
}

void XConsole::clearScreen()
{
	consoleHistory.clear();
	consoleTextBufferHeight = 0;

}


bool XConsole::switchGetKeyPressMode()
{
	return getKeyPressSwitch = !getKeyPressSwitch;
}


void XConsole::setAlpha(char alpha)
{
	if(alpha > 100)
		alpha = 100;
	
	unsigned char* ptr = (unsigned char*)&consoleColor;
	ptr[3] = 255*(alpha/100.0);

}

void XConsole::getKeyPress(WPARAM* wParam)
{
	XBot* xbot = XBot::getXBot();
	
	bool shift = GetKeyState(VK_SHIFT) & 0x80;

	if(*wParam == /*0x43*/VK_MULTIPLY) //&& GetKeyState(VK_CONTROL) & 0x80)
		return;
	
	
	switch(*wParam)
	{
	case VK_BACK:
		if(currentLineStr.size() > 1 && caretPos > 0)
		{
			currentLineStr.erase(caretPos - 1,1);
			caretPos--;
		}
		break;
	case VK_DELETE:
		if(currentLineStr.size() > 1 && currentLineStr.size() > caretPos + 1)
		{
			currentLineStr.erase(caretPos, 1);
		}
		break;
	case VK_TAB:
		if(currentLineStr.size() > 0)
		{
			autoCompleteLine();
		}
		break;
	case VK_PRIOR:
		{
			if(shift)
			{
				pgUpShift += 10;
				if(pgUpShift > consoleTextBufferHeight - 20)
					pgUpShift = consoleTextBufferHeight - 20;
			}
		}
		break;
	case VK_NEXT:
		{
			if(shift)
			{
				pgUpShift -= 10;
				if(pgUpShift < 0)
					pgUpShift = 0;
			}
		}
		break;
	case VK_LEFT:
		caretPos--;
		if(caretPos < 0)
			caretPos = 0;
		break;
	case VK_RIGHT:
		caretPos++;
		if(caretPos > currentLineStr.size()-1)
			caretPos = currentLineStr.size()-1;
		break;
	case VK_UP:
		currentLineStr.resize(lastLineStr.size());
		currentLineStr.replace(0, lastLineStr.size() ,lastLineStr);
		caretPos = lastLineStr.size()-1;
		break;
	case VK_RETURN: 
		onReturnPress();
		break;

	default:
		unsigned char c = charFromVK(*wParam, shift);
		if(c != 0)
		{
			currentLineStr.insert(caretPos, 1 , c);
			caretPos++;
		}
		break;
	}
	
	
	
	
	*wParam = 0;
	time = GetTickCount();

}

void XConsole::autoCompleteLine()
{
	string word("");
	
	
	if(commandHandler->autoCompleteLine(&currentLineStr, &word))
	{
		currentLineStr = word;
		caretPos = currentLineStr.size();
		currentLineStr.append(" ");
	}
	else if(word.size() > 0 ) 
	{
		addHistoryLine(word.c_str());
		currentLineStr.append(" ");
	}

}

void XConsole::onReturnPress()
{
	char* result;

	commandHandler->processCommand(currentLineStr.c_str(), result);
	if(result)
		addHistoryLine(result);
	
	lastLineStr.resize(currentLineStr.size());
	lastLineStr.replace(0, currentLineStr.size(), currentLineStr);

	currentLineStr.erase();
	currentLineStr.append(" ");
	caretPos = 0;
	delete [] result;
	
}
void XConsole::addHistoryLine(const char* str, D3DCOLOR color)
{
	addHistoryLine(str);
	consoleHistory.front().color = color;

}

void XConsole::popUp(bool mode)
{
	if(mode)
	{
		if(!getIsOut() || slidingIn)
		{
			isOut = false;
			slideOut();
			getKeyPressSwitch = false;
			isPopUpping = true;
		}
		else
			time = GetTickCount(); 
	}
	else
	{
		isPopUpping = false;
		getKeyPressSwitch = true;
	}
}


void XConsole::addHistoryLine(const char* str)
{

	if(consoleHistory.size() > MAX_CONSOLE_TEXT_BUFFER)
	{
		clearScreen();
		addHistoryLine("Console History Cleared! !1MByte Buffer Overflow", 0xFFFF0000);
	}
	
	consoleString s("\n> ");
	s.append(str);
	s.append("\n");
	
	RECT tmp = {consoleHistoryFontPos.left,consoleHistoryFontPos.top,consoleHistoryFontPos.right,consoleHistoryFontPos.bottom};
	s.pixelHeight = consoleHistoryFont->DrawText(s.c_str(), -1, &tmp, DT_LEFT | DT_EDITCONTROL | DT_WORDBREAK | DT_CALCRECT, s.color);
	consoleTextBufferHeight += s.pixelHeight;
	
	consoleHistory.insert(consoleHistory.begin(),s);
	pgUpShift = 0;
}


void XConsole::addSprintfLine(const char* str, ...)
{
	char buffer[1024];
	va_list	args;

	va_start( args, str );
	vsprintf( buffer, str, args );
	va_end( args );
	
	addHistoryLine(buffer);
}

void XConsole::buildFullCommandList()
{
	if(commandHandler)
		commandHandler->buildFullCommandList();
}

void XConsole::buildLiteCommandList()
{
	if(commandHandler)
		commandHandler->buildLiteCommandList();
}

unsigned char XConsole::charFromVK(WPARAM vk, bool shift)
{
	
	switch(vk)
	{
		case VK_SPACE:	return ' ';
		case 0x30:if(shift) return '='; else   return '0';
		case VK_NUMPAD0:return '0';
		case 0x31:if(shift) return '!'; else   return '1';
		case VK_NUMPAD1:return '1';
		case 0x32:if(shift) return '"'; else   return '2';
		case VK_NUMPAD2:return '2';
		case 0x33:if(shift) return '£'; else   return '3';
		case VK_NUMPAD3:return '3';
		case 0x34:if(shift) return '$'; else   return '4';
		case VK_NUMPAD4:return '4';
		case 0x35:if(shift) return '%'; else   return '5';
		case VK_NUMPAD5:return '5';
		case 0x36:if(shift) return '&'; else   return '6';
		case VK_NUMPAD6:return '6';
		case 0x37:if(shift) return '/'; else   return '7';
		case VK_NUMPAD7:return '7';
		case 0x38:if(shift) return '('; else   return '8';
		case VK_NUMPAD8:return '8';
		case 0x39:if(shift) return ')'; else   return '9';
		case VK_NUMPAD9:return '9';
		case 0x41: if(shift) return 'A'; else   return 'a';
		case 0x42: if(shift) return 'B'; else   return 'b';
		case 0x43: if(shift) return 'C'; else  	return 'c';
		case 0x44: if(shift) return 'D'; else 	return 'd';
		case 0x45: if(shift) return 'E'; else 	return 'e';
		case 0x46: if(shift) return 'F'; else 	return 'f';
		case 0x47: if(shift) return 'G'; else 	return 'g';
		case 0x48: if(shift) return 'H'; else 	return 'h';
		case 0x49: if(shift) return 'I'; else 	return 'i';
		case 0x4A: if(shift) return 'J'; else 	return 'j';
		case 0x4B: if(shift) return 'K'; else 	return 'k';
		case 0x4C: if(shift) return 'L'; else 	return 'l';
		case 0x4D: if(shift) return 'M'; else 	return 'm';
		case 0x4E: if(shift) return 'N'; else 	return 'n';
		case 0x4F: if(shift) return 'O'; else 	return 'o';
		case 0x50: if(shift) return 'P'; else 	return 'p';
		case 0x51: if(shift) return 'Q'; else 	return 'q';
		case 0x52: if(shift) return 'R'; else 	return 'r';
		case 0x53: if(shift) return 'S'; else 	return 's';
		case 0x54: if(shift) return 'T'; else 	return 't';
		case 0x55: if(shift) return 'U'; else 	return 'u';
		case 0x56: if(shift) return 'V'; else 	return 'v';
		case 0x57: if(shift) return 'W'; else 	return 'w';
		case 0x58: if(shift) return 'X'; else 	return 'x';
		case 0x59: if(shift) return 'Y'; else   return 'y';
		case 0x5A: if(shift) return 'Z'; else   return 'z';
		case VK_ADD:		return '+';
		case VK_SUBTRACT:	return '-';
		case VK_MULTIPLY:	return '*';
		case VK_DIVIDE:		return '/';
		case 0xBB: if(shift) return '*'; else 	return '+';
		case 0xBC: if(shift) return ';'; else 	return ',';
		case 0xBD: if(shift) return '_'; else 	return '-';
		case 0xBE: if(shift) return ':'; else 	return '.';
		case 0xDE:  return '\'';
		case 0xE2: if(shift) return '>'; else   return '<';



		default: return 0;
	
	}


}
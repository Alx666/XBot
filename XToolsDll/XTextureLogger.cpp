#include "XTextureLogger.h"

XTextureLogger::XTextureLogger()
{
	backgroundTextures.clear();
	logTextures.clear();

	loggerFontColor = D3DCOLOR_RGBA(255, 0, 0, 255);

	textRectStart.left = 100;
	textRectStart.top = 100;
	textRectStart.right = 400;
	textRectStart.bottom = 125;

	textRect = textRectStart;
	texLogOut = fopen("texture_log.txt","w");
	sprintf(outStr, "niente");
	phase = 0;
	nBackground = 0;
	nLogTextures = 0;
	logtime = 0;
	nLog = 0;
	logInProgres = false;
	setText();


	sprintf(outStr, "Log\t\tCRC\t\t\tFormat\n");
	fwrite(outStr, sizeof(char), strlen(outStr), texLogOut);
}

XTextureLogger::~XTextureLogger()
{
	fclose(texLogOut);
}

void XTextureLogger::setDevice(LPDIRECT3DDEVICE8 d3dDeviceRef)
{
	d3dDevice = d3dDeviceRef;

	LOGFONT LogFont = {15, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Arial"};
	D3DXCreateFontIndirect(d3dDevice, &LogFont, &loggerFont);	
}

void XTextureLogger::draw()
{
	loggerFont->Begin();

		loggerFont->DrawText(str1, -1, &textRect, DT_LEFT, loggerFontColor);
		textRect.top = textRect.bottom;
		textRect.bottom+=25;
		loggerFont->DrawText(str2, -1, &textRect, DT_LEFT, loggerFontColor);
		textRect.top = textRect.bottom;
		textRect.bottom+=25;
		loggerFont->DrawText(str3, -1, &textRect, DT_LEFT, loggerFontColor);

		textRect = textRectStart;

	loggerFont->End();
}

void XTextureLogger::setText() // gli altri case servirebbero per accedere a dei sub menu (da fare eventualmente)
{
	switch(phase)
	{
	case 0:
		{
			sprintf(str1, "[Z] Set Background Textures (%i set)", nBackground);
			sprintf(str2, "[X] Log textures (%i set)", nLogTextures);
			sprintf(str3, "[C] clear lists");

		} break;
	case 1:
		{
			sprintf(str1, "[Z] Stop logging...");
			sprintf(str2, "[X] ...");
			sprintf(str3, "[C] ...");

		} break;

	case 2:
		{
			sprintf(str1, "[Z] ...");
			sprintf(str2, "[X] Stop logging...");
			sprintf(str3, "[C] ...");

		} break;

	case 3:
		{
			sprintf(str1, "[Z] Set Background Textures (%i set)", nBackground);
			sprintf(str2, "[X] Log textures (%i set)", nLogTextures);
			sprintf(str3, "[C] clear lists");

		} break;

	}
}

void XTextureLogger::logToFile()
{
	fwrite(outStr, sizeof(char),strlen(outStr),texLogOut);
}


void XTextureLogger::startLogging()
{
	logInProgres = true;
	phase = 1;
	setText();
}

void XTextureLogger::stopLogging()
{
	logInProgres = false;
	nBackground = backgroundTextures.size();
	nLogTextures = logTextures.size();

	phase = 0;
	setText();
}

void XTextureLogger::logTexture(FAKE_IDirect3DTexture8 *pTexture)
{
	if(!logInProgres)
		return;

	switch(phase)
	{
	case 1: //fase di log del background
		{
			if(!IsInBackgroundTextureList(pTexture))
			{
				backgroundTextures.push_back(pTexture);
			}
		} break;
	case 2: //fase di log delle texture utili
		{
			if(!IsInBackgroundTextureList(pTexture) && !IsInLogTextureList(pTexture))
			{
				logTextures.push_back(pTexture);
				sprintf(outStr, "%i\t\t0x%x\t\t%i*%i\t\t\n", nLog, pTexture->Crc32, pTexture->Width, pTexture->Height);
				fwrite(outStr, sizeof(char), strlen(outStr), texLogOut);
				nLog++;
			}
		} break;
	}


}

void XTextureLogger::XPression()
{
	switch(phase)
	{
	case 0: compareTextures(); break;
	case 2: stopLogging(); break;
	}
}

void XTextureLogger::ZPression()
{
	switch(phase)
	{
	case 0:	startLogging(); break;
	case 1: stopLogging();	break;
	}
}

void XTextureLogger::CPression()
{
	switch(phase)
	{
	case 0:	 clear(); break;
	}
}

void XTextureLogger::clear()
{
	backgroundTextures.clear(); 
	logTextures.clear();
	nBackground = backgroundTextures.size();
	nLogTextures = logTextures.size();
	setText();
}


bool XTextureLogger::IsInBackgroundTextureList(FAKE_IDirect3DTexture8* tex)
{
	for (unsigned int i = 0; i < backgroundTextures.size(); i++)
		if (tex == backgroundTextures[i])
			return true;
	return false;
}


bool XTextureLogger::IsInLogTextureList(FAKE_IDirect3DTexture8* tex)
{
	for (unsigned int i = 0; i < logTextures.size(); i++)
		if (tex == logTextures[i])
			return true;
	return false;
}

void XTextureLogger::compareTextures()
{
	phase = 2;
	logInProgres = true;
	//logTextures.clear();
	setText();
}

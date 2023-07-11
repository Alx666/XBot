#include "xbotlauncherdialog.h"
#include <qevent.h>
#include "LineEditEx.h"
#include "XListView.h"
#include <qlineedit.h>
#include <qfiledialog.h> 
#include <qapplication.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qdatetime.h>

#include <windows.h>



//DEBUG INCLUDE
#include <qmessagebox.h> 


#define DETOURS

#ifdef DETOURS
	#include "detours\detours.h"
#endif

XBotLauncherDialog::XBotLauncherDialog( QWidget* parent, const char* name, bool modal, WFlags f )
	: XBotLauncherDialogBase( parent, name, modal, f )
{
	connect((QObject*)pbLaunch, SIGNAL( clicked() ), this, SLOT( slotStart() ) );
	connect((QObject*)pbChoose, SIGNAL( clicked() ), this, SLOT( slotChoosePath() ) );
	connect((QObject*)pbCancel,	SIGNAL( clicked() ), this, SLOT( slotQuit() ) );
	connect((QObject*)pbDefault,SIGNAL( clicked() ), this, SLOT( slotBuildDefault() ) );

	configChanged = false;

	xconfig = new XConfig();

	lePathToUT->setText(xconfig->pathToUT);
	leExeParam->setText(xconfig->exeParam);

	leMasterSwitch->setKey(xconfig->masterSwitch);
	leDodge->setKey(xconfig->enableDodge);
	leResetShield->setKey(xconfig->resetCounterShield);
	leResetDDamage->setKey(xconfig->resetCounterDDamage);
	leResetRedeem->setKey(xconfig->resetCounterRedeem);

	int i = 0;
	while(ipTable->add(xconfig->playerlist[i]))
		i++;

	for( i = 0; i<MAX_PLAYERS;i++)
	{
		xconfig->playerlist[i].name = 0;
		xconfig->playerlist[i].codedIp = 0;
	}

	//leDodge->setDisabled(true);
	//leDodge->setText("disabled");

	//leResetRedeem->setDisabled(true);
	//leResetRedeem->setText("disabled");
	

	//PERSONALIZATION
	/*
	QDate* expire = new QDate(2005,4,20);
	QDate current = QDate::currentDate();

	if(current >= *expire)
		exit(0);
	*/


}



void XBotLauncherDialog::slotSaveConfig()
{
	pbLaunch->setText("&Launch");
	pbLaunch->setAccel( QKeySequence(  "Alt+L" ));
	pbLaunch->disconnect();
	connect((QObject*)pbLaunch,SIGNAL( clicked() ), this, SLOT( slotStart() ) );

	
	xconfig->pathToUT = (char*)(lePathToUT->text()).data();
	xconfig->exeParam = (char*)(leExeParam->text()).data();
	
	xconfig->enableDodge = leDodge->getKey();
	xconfig->masterSwitch = leMasterSwitch->getKey();
	xconfig->resetCounterShield = leResetShield->getKey();
	xconfig->resetCounterDDamage = leResetDDamage->getKey();
	xconfig->resetCounterRedeem = leResetRedeem->getKey();

	//Salvataggio in file INI degli ip
	QListViewItemIterator it((QListView*)ipTable);

	for(int i = 0; it.current(); i++)
	{
		xconfig->playerlist[i].name = (char*)(it.current()->text(0)).ascii();
		xconfig->playerlist[i].codedIp = XListView::checkAndConvert(it.current()->text(1));
		it++;
	}


	xconfig->writeSettings();
	configChanged = false;

	//QMessageBox::information(this, "XBot Launcher", "Config Saved");
}


void XBotLauncherDialog::slotChoosePath()
{
	//if(!configChanged)
	//	return;

	QString initialDir = lePathToUT->text();

	QString selectedFile = QFileDialog::getOpenFileName(initialDir, "Executables (*.exe)", this, 0, "Specify Path to Unreal 2004 executable");

	//If the user accepts changes, change default value
	if(!selectedFile.isEmpty()) 
		lePathToUT->setText(selectedFile);
}


void XBotLauncherDialog::slotQuit()
{
	qApp->quit();
}

void XBotLauncherDialog::slotBuildDefault()
{
	xconfig->buildDefault();

	lePathToUT->setText(xconfig->pathToUT);
	leExeParam->setText(xconfig->exeParam);
	//leDodge->setKey(xconfig->enableDodge);
	leMasterSwitch->setKey(xconfig->masterSwitch);
	leResetShield->setKey(xconfig->resetCounterShield);
	leResetDDamage->setKey(xconfig->resetCounterDDamage);
	//leResetRedeem->setKey(xconfig->resetCounterRedeem);

	QMessageBox::information(this, "Message", "Default config restored");
}


void XBotLauncherDialog::slotStart()
{

	char* path		= (char*)(lePathToUT->text()).data();
	char* param		= (char*)(leExeParam->text()).data();
	char DllName[256];
	
	_STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);


		#ifdef DETOURS
			sprintf(DllName,"XTools.dll");
		#else
			sprintf(DllName,"%s\\XTools.dll",xconfig->launchPath);
		#endif



	#ifdef DETOURS

		if(!DetourCreateProcessWithDllA(path, param, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE,
								   NULL, NULL, &si, &pi,DllName , NULL))
			QMessageBox::information(this, "Error", "ut2004.exe failed to load!");
		
		xconfig->threadID = pi.dwThreadId;
		
		slotSaveConfig();

	#else
		
		CreateProcessA(path, param, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE,
								   NULL, NULL, &si, &pi);
		
		xconfig->threadID = pi.dwThreadId;
		slotSaveConfig();

		void* addr = VirtualAllocEx(pi.hProcess ,NULL, strlen(DllName) + 1, MEM_COMMIT ,PAGE_READWRITE );
		WriteProcessMemory(pi.hProcess, addr, (void*)DllName, strlen(DllName) + 1, NULL);
	
		HANDLE hThread = CreateRemoteThread(pi.hProcess,NULL,NULL,(LPTHREAD_START_ROUTINE)(GetProcAddress(GetModuleHandleA("Kernel32"),"LoadLibraryA")),addr,NULL,NULL);
	
		WaitForSingleObject( hThread, INFINITE );

		// Get handle of the loaded module
		//GetExitCodeThread( hThread, &hLibModule );

		// Clean up
		CloseHandle( hThread );
		VirtualFreeEx( pi.hProcess, addr, strlen(DllName) + 1, MEM_RELEASE );

	#endif

		slotQuit();
}
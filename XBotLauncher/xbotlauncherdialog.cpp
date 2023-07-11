#include "xbotlauncherdialog.h"
#include <qevent.h>
#include "LineEditEx.h"
#include "XListView.h"
#include <qlineedit.h>
#include <qfiledialog.h> 
#include <qapplication.h>
#include <qpushbutton.h>
#include <qmessagebox.h>

#include <windows.h>
#include "detours\detours.h"


//DEBUG INCLUDE
#include <qmessagebox.h> 


#define DETOURS

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

	boxStealth->setChecked(xconfig->stealthMode);

	leEnableAim->setKey(xconfig->enableAim);
	leHeadShot->setKey(xconfig->enableHeadShot);
	leDodge->setKey(xconfig->enableDodge);
	leMenuUp->setKey(xconfig->menuUp);
	leMenuDown->setKey(xconfig->menuDown);
	leMenuPlus->setKey(xconfig->menuPlus);
	leMenuSub->setKey(xconfig->menuMinus);
	lePriFire->setKey(xconfig->priFire);
	leAltFire->setKey(xconfig->altFire);
	leJumpKey->setKey(xconfig->jump);
	leMasterSwitch->setKey(xconfig->masterSwitch);
	leResetShield->setKey(xconfig->resetCounterShield);
	leResetDDamage->setKey(xconfig->resetCounterDDamage);
	leResetRedeem->setKey(xconfig->resetCounterRedeem);
	leAutoSwap->setKey(xconfig->autoSwap);

	sliMouseSens->setValue(xconfig->mouseSpeed*4);
	mouseValue->display(xconfig->mouseSpeed*4);

	int i = 0;
	while(ipTable->add(xconfig->playerlist[i]))
		i++;

	for( i = 0; i<MAX_PLAYERS;i++)
	{
		xconfig->playerlist[i].name = 0;
		xconfig->playerlist[i].codedIp = 0;
	}


	lePriFire->setDisabled(true);
	
	//FILLS THE MODS COMBO BOX
	QFile FragOpsDLL("FragOps.dll");
	
	if(FragOpsDLL.exists())
		modsBox->insertItem("FragOps");

}



void XBotLauncherDialog::slotSaveConfig()
{
	pbLaunch->setText("&Launch");
	pbLaunch->setAccel( QKeySequence(  "Alt+L" ));
	pbLaunch->disconnect();
	connect((QObject*)pbLaunch,SIGNAL( clicked() ), this, SLOT( slotStart() ) );

	
	xconfig->pathToUT = (char*)(lePathToUT->text()).data();
	xconfig->exeParam = (char*)(leExeParam->text()).data();
	
	xconfig->stealthMode =  boxStealth->isChecked();

	xconfig->enableAim = leEnableAim->getKey();
	xconfig->enableDodge = leDodge->getKey();
	xconfig->enableHeadShot = leHeadShot->getKey();
	xconfig->menuUp = leMenuUp->getKey();
	xconfig->menuDown = leMenuDown->getKey();
	xconfig->menuPlus = leMenuPlus->getKey();
	xconfig->menuMinus = leMenuSub->getKey();
	xconfig->priFire = lePriFire->getKey();
	xconfig->altFire = leAltFire->getKey();
	xconfig->jump = leJumpKey->getKey();
	xconfig->mouseSpeed = mouseValue->value();
	xconfig->masterSwitch = leMasterSwitch->getKey();
	xconfig->resetCounterShield = leResetShield->getKey();
	xconfig->resetCounterDDamage = leResetDDamage->getKey();
	xconfig->resetCounterRedeem = leResetRedeem->getKey();
	xconfig->autoSwap = leAutoSwap->getKey();

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

	sliMouseSens->setValue(xconfig->mouseSpeed*4);
	mouseValue->display(xconfig->mouseSpeed*4);

	lePathToUT->setText(xconfig->pathToUT);
	leExeParam->setText(xconfig->exeParam);
	leEnableAim->setKey(xconfig->enableAim);
	leDodge->setKey(xconfig->enableDodge);
	leHeadShot->setKey(xconfig->enableHeadShot);
	leMenuUp->setKey(xconfig->menuUp);
	leMenuDown->setKey(xconfig->menuDown);
	leMenuPlus->setKey(xconfig->menuPlus);
	leMenuSub->setKey(xconfig->menuMinus);
	lePriFire->setKey(xconfig->priFire);
	leAltFire->setKey(xconfig->altFire);
	leJumpKey->setKey(xconfig->jump);
	leMasterSwitch->setKey(xconfig->masterSwitch);
	leResetShield->setKey(xconfig->resetCounterShield);
	leResetDDamage->setKey(xconfig->resetCounterDDamage);
	leResetRedeem->setKey(xconfig->resetCounterRedeem);
	leAutoSwap->setKey(xconfig->autoSwap);

	QMessageBox::information(this, "Message", "Default config restored");
}


void XBotLauncherDialog::slotStart()
{

	char* path		= (char*)(lePathToUT->text()).data();
	char* param		= (char*)(leExeParam->text()).data();
	char DllName[256];
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	if(modsBox->currentText() == "none")
		#ifdef DETOURS
			sprintf(DllName,"UT2k4.dll");
		#else
			sprintf(DllName,"%s\\UT2k4.dll",xconfig->launchPath);
		#endif

	else if(modsBox->currentText() == "FragOps")
	{
		#ifdef DETOURS
			sprintf(DllName, "FragOps.dll");
		#else
			sprintf(DllName ,"%s\\FragOps.dll",xconfig->launchPath);
		#endif
		
		char s[256];
		sprintf(s," -mod=FragOps %s",param);
		param = s;
		
	}

	#ifdef DETOURS

		if(!DetourCreateProcessWithDll(path, param, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE,
								   NULL, NULL, &si, &pi,DllName , NULL))
			QMessageBox::information(this, "Error", "ut2004.exe failed to load!");
		
		xconfig->threadID = pi.dwThreadId;
		
		slotSaveConfig();

	#else
		
		CreateProcess(path, param, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE,
								   NULL, NULL, &si, &pi);
		
		xconfig->threadID = pi.dwThreadId;
		slotSaveConfig();

		void* addr = VirtualAllocEx(pi.hProcess ,NULL, strlen(DllName) + 1, MEM_COMMIT ,PAGE_READWRITE );
		WriteProcessMemory(pi.hProcess, addr, (void*)DllName, strlen(DllName) + 1, NULL);
	
		HANDLE hThread = CreateRemoteThread(pi.hProcess,NULL,NULL,(LPTHREAD_START_ROUTINE)(GetProcAddress(GetModuleHandle("Kernel32"),"LoadLibraryA")),addr,NULL,NULL);
	
		WaitForSingleObject( hThread, INFINITE );

		// Get handle of the loaded module
		//GetExitCodeThread( hThread, &hLibModule );

		// Clean up
		CloseHandle( hThread );
		VirtualFreeEx( pi.hProcess, addr, strlen(DllName) + 1, MEM_RELEASE );

	#endif

		slotQuit();
}
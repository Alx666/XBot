/****************************************************************************
** Form implementation generated from reading ui file '.\xbotlauncherdialogbase.ui'
**
** Created: lun 28. giu 02:25:17 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.3   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "xbotlauncherdialogbase.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include "LineEditEx.h"
#include <qlabel.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qslider.h>
#include "xlistview.h"


#include <qwhatsthis.h>
#include <qtooltip.h>

#include <qapplication.h>

/*
 *  Constructs a XBotLauncherDialogBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
XBotLauncherDialogBase::XBotLauncherDialogBase( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "XBotLauncherDialogBase" );
    setSizeGripEnabled( FALSE );

	setCaption("XBot Launcher 1.95");

	//Launch Button
    pbLaunch = new QPushButton( this, "pbLaunch" );
    pbLaunch->setGeometry(QRect( 10, 181, 82, 26 ) );
    pbLaunch->setText("&Launch");
    pbLaunch->setAccel( QKeySequence("Alt+L") );

	//Default Button
    pbDefault = new QPushButton( this, "pbDefault" );
    pbDefault->setGeometry( QRect( 196, 181, 82, 26 ) );
    pbDefault->setText( "&Default"  );
    pbDefault->setAccel( QKeySequence(  "Alt+D" ) );

	//Cancel Button
    pbCancel = new QPushButton( this, "pbCancel" );
    pbCancel->setGeometry(QRect( 279, 181, 82, 26 ) );
    pbCancel->setText("&Cancel");
    pbCancel->setAccel( QKeySequence("Alt+C") );



	//Setup the Tab Widget
    tabWidget = new QTabWidget( this, "tabWidget" );
    tabWidget->setGeometry(QRect( 0, 0, 360, 180 ) );


    tabPath = new QWidget( tabWidget, "tabPath" );
	tabSettings = new QWidget(tabWidget, "tabSettings");
	tabKeys = new QWidget( tabWidget, "tabKeys" );
	tabSock = new QWidget(tabWidget, "tabSock");

	tabWidget->insertTab( tabPath, QString("XPath")   );
	tabWidget->insertTab( tabSettings, QString("XSettings"));
	tabWidget->insertTab( tabKeys, QString("XKeys") );
	tabWidget->insertTab(tabSock, QString("XSocket"));



	//Create Components and insert them in the XPat Tab
	
	xbotLogo = new XGlLogo(tabPath, "Xlogo");
	xbotLogo->setGeometry(QRect(10, 10, 140, 130));

    labelPath = new QLabel( tabPath, "labelPath" );
    labelPath->setGeometry( QRect( 160, 10, 110, 20 ) );
	labelPath->setText("Path to UT2004.exe");

    lePathToUT = new QLineEdit( tabPath, "lePathToUT");
    lePathToUT->setGeometry( QRect( 160, 30, 155, 20 ));
	

	labelParam = new QLabel(tabPath, "labelParam");
	labelParam->setGeometry(QRect(160, 55, 50, 20));
	labelParam->setText("Param:");
	leExeParam = new QLineEdit(tabPath, "leExeParam");
	leExeParam->setGeometry(QRect( 205, 55, 110, 20));

	boxStealth = new QCheckBox(tabPath, "boxStealth");
	boxStealth->setGeometry(QRect(340, 134, 13, 13));
	labelStealthMode = new QLabel(tabPath, "labelLeakedMode");
	labelStealthMode->setText("Stealth Mode:");
	labelStealthMode->setGeometry( QRect( 270, 130, 65, 20 ) );


    pbChoose = new QPushButton( tabPath, "pbChoose" );
	pbChoose->setText("...");
    pbChoose->setGeometry( QRect( 320, 29, 30, 22 ) );

	modsBox = new QComboBox(tabPath , "modsBox");
	modsBox->setGeometry(QRect( 205, 85, 115, 20));
	modsBox->insertItem("none");
	labelModsBox = new QLabel(tabPath, "labelParam");
	labelModsBox->setGeometry(QRect(160, 85, 30, 20));
	labelModsBox->setText("Mods:");

	//Inpostazione delle XSettings
	groupGameKeys = new QGroupBox( tabSettings, "groupGameKeys" );
	groupGameKeys->setGeometry( QRect( 0, 0, 100, 150 ) );
	groupGameKeys->setTitle("Game Keys");

	lePriFire = new LineEditEx(groupGameKeys, "leAltFire");
	lePriFire->setGeometry( QRect( 50, 20, 43, 20 ) );

    labelPriFire = new QLabel(groupGameKeys, "labelAltFire");
    labelPriFire->setText("Fire:");
    labelPriFire->setGeometry( QRect( 5, 20, 40, 20 ) );

	leAltFire = new LineEditEx(groupGameKeys, "leAltFire");
	leAltFire->setGeometry( QRect( 50, 40, 43, 20 ) );

    labelAltFire = new QLabel(groupGameKeys, "labelAltFire");
    labelAltFire->setText("Alt.Fire:");
    labelAltFire->setGeometry( QRect( 5, 40, 40, 20 ) );

	leJumpKey = new LineEditEx(groupGameKeys, "leJumpKey");
	leJumpKey->setGeometry(QRect(50, 60, 43, 20));

	labelJumpKey = new QLabel(groupGameKeys, "labelJumpKey");
	labelJumpKey->setText("Jump:");
	labelJumpKey->setGeometry( QRect( 5, 60, 40, 20 ) );


	lePriFire->setBuddy(leAltFire);
	leAltFire->setBuddy(leJumpKey);
	leJumpKey->setBuddy(lePriFire);

	groupMouseSpeed = new QGroupBox( tabSettings, "groupMouseSpeed" );
	groupMouseSpeed->setGeometry( QRect(100, 0, 255, 70 ) );
	groupMouseSpeed->setTitle("Mouse Speed");

	//sliMouseSens = new QSlider(groupMouseSpeed, "mouse slider" );
	sliMouseSens = new QSlider(0, 100, 4, 0, QSlider::Horizontal, groupMouseSpeed, "mouse slider" );
    sliMouseSens->setTickmarks( QSlider::Left );
	sliMouseSens->setGeometry(QRect(10, 30, 160, 20 ));

	mouseValue = new XLCDNumber(4, groupMouseSpeed);
	mouseValue->setMode(QLCDNumber::Dec);
	mouseValue->setSmallDecimalPoint(true);
	mouseValue->setSegmentStyle(QLCDNumber::Flat);
	mouseValue->setGeometry(QRect(172, 10, 80, 56 ));

	connect( sliMouseSens, SIGNAL(valueChanged(int)), mouseValue, SLOT(display(int)));

	//TIMERS
	groupTimers = new QGroupBox( tabSettings, "groupTimers");
	groupTimers->setGeometry( QRect(100, 70, 255, 80 ) );

	labelResetShield = new QLabel( groupTimers, "labelResetShield" );
	labelResetShield->setGeometry( QRect(10, 10, 110, 25 ) );
	labelResetShield->setText("Timer Shield:");
	leResetShield  = new LineEditEx( groupTimers, "leResetShield");
	leResetShield->setGeometry( QRect( 93, 10, 43, 20 ) );

	labelResetDDamage = new QLabel( groupTimers, "labelResetDDamage" );
	labelResetDDamage->setGeometry( QRect(10, 30, 110, 25 ) );
	labelResetDDamage->setText("Timer DDamage:");
	leResetDDamage = new LineEditEx( groupTimers, "leResetDDamage");
	leResetDDamage->setGeometry( QRect( 93, 30, 43, 20 ) );

	labelResetRedeem = new QLabel( groupTimers, "labelResetRedeem" );
	labelResetRedeem->setGeometry( QRect(10, 50, 110, 25 ) );
	labelResetRedeem->setText("Timer Redeem:");
	leResetRedeem  = new LineEditEx( groupTimers, "leResetRedeem");
	leResetRedeem->setGeometry( QRect( 93, 50, 43, 20 ) );

	leResetRedeem->setBuddy(leResetShield);
	leResetDDamage->setBuddy(leResetRedeem);
	leResetShield->setBuddy(leResetDDamage);


	//Create Components and insert them in the XConfig tab
	///////////////////////////////////////////////////////

	//Toggle Keys
    groupToggleKeys = new QGroupBox( tabKeys, "groupToggleKeys" );
    groupToggleKeys->setGeometry( QRect( 0, 0, 170, 150 ) );
	groupToggleKeys->setTitle("Quick Keys");

    QWidget* privateLayoutWidget_2 = new QWidget( groupToggleKeys, "layGridToggleKeys" );
    privateLayoutWidget_2->setGeometry( QRect( 10, 15, 155, 120 ) );
    layGridToggleKeys = new QGridLayout( privateLayoutWidget_2, 1, 1, 11, 3, "layGridToggleKeys"); 

    leDodge = new LineEditEx( privateLayoutWidget_2, "leDodge");
    layGridToggleKeys->addWidget( leDodge, 4, 1 );
    labelDodge = new QLabel( privateLayoutWidget_2, "labelDodge" );
	labelDodge->setText("Dodge mode:");
    layGridToggleKeys->addWidget( labelDodge, 4, 0 );

    leEnableAim = new LineEditEx( privateLayoutWidget_2, "leEnableAim", leDodge);
    layGridToggleKeys->addWidget( leEnableAim, 3, 1 );
    labelEnableAim = new QLabel( privateLayoutWidget_2, "labelEnableAim" );
	labelEnableAim->setText("Enable Aim:");
    layGridToggleKeys->addWidget( labelEnableAim, 3, 0 );

	leMasterSwitch = new LineEditEx( privateLayoutWidget_2, "leMasterSwitch", leEnableAim);
	layGridToggleKeys->addWidget( leMasterSwitch, 2, 1 );
    labelMasterSwitch = new QLabel( privateLayoutWidget_2, "labelMasterSwitch" );
	labelMasterSwitch->setText("Master Switch:");
    layGridToggleKeys->addWidget( labelMasterSwitch, 2, 0 );

	leHeadShot = new LineEditEx( privateLayoutWidget_2, "leHeadShot", leMasterSwitch);
	layGridToggleKeys->addWidget( leHeadShot, 1, 1 );
    labelHeadShot = new QLabel( privateLayoutWidget_2, "labelHeadShot" );
	labelHeadShot->setText("HeadShot Mode:");
    layGridToggleKeys->addWidget( labelHeadShot, 1, 0 );

	leAutoSwap = new LineEditEx( privateLayoutWidget_2, "leAutoSwap", leHeadShot);
	layGridToggleKeys->addWidget( leAutoSwap, 0, 1 );
    labelAutoSwap = new QLabel( privateLayoutWidget_2, "labelAutoSwap" );
	labelAutoSwap->setText("AutoSwap Mode:");
    layGridToggleKeys->addWidget( labelAutoSwap, 0, 0 );


	//////////////////////////Menu Keys
    groupMenuKeys = new QGroupBox( tabKeys, "groupMenuKeys" );
    groupMenuKeys->setGeometry( QRect( 170, 0, 185, 150 ) );
	groupMenuKeys->setTitle( tr( "Menu Navigation" ) );


    QWidget* privateLayoutWidget = new QWidget( groupMenuKeys, "layGridMenuKeys" );
    privateLayoutWidget->setGeometry( QRect( 30, 20, 130, 120 ) );
    layGridMenuKeys = new QGridLayout(privateLayoutWidget, 1, 1, 11, 0, "layGridMenuKeys"); 


    leMenuSub = new LineEditEx( privateLayoutWidget, "leMenuSub", leAutoSwap);
    layGridMenuKeys->addWidget( leMenuSub, 3, 1 );
    labelMenuMinus = new QLabel( privateLayoutWidget, "labelMenuMinus" );
	labelMenuMinus->setText("Menu ( - ):");
    layGridMenuKeys->addWidget( labelMenuMinus, 3, 0 );

    leMenuPlus = new LineEditEx( privateLayoutWidget, "leMenuPlus", leMenuSub);
    layGridMenuKeys->addWidget( leMenuPlus, 2, 1 );
    labelMenuPlus = new QLabel( privateLayoutWidget, "labelMenuPlus" );
	labelMenuPlus->setText("Menu ( + ):");
    layGridMenuKeys->addWidget( labelMenuPlus, 2, 0 );

    leMenuDown = new LineEditEx( privateLayoutWidget, "leMenuDown", leMenuPlus);
    layGridMenuKeys->addWidget( leMenuDown, 1, 1 );
    labelMenuDown = new QLabel( privateLayoutWidget, "labelMenuDown" );
	labelMenuDown->setText("Menu down:");
    layGridMenuKeys->addWidget( labelMenuDown, 1, 0 );
    	
	leMenuUp = new LineEditEx( privateLayoutWidget, "leMenuUp", leMenuDown);
    layGridMenuKeys->addWidget(leMenuUp, 0, 1 );
    labelMenuUp = new QLabel( privateLayoutWidget, "labelMenuUp" );
	labelMenuUp->setText("Menu up:");
    layGridMenuKeys->addWidget( labelMenuUp, 0, 0 );

	leDodge->setBuddy(leMenuUp);

	//Create and insert object in the XSock Tab
	/////////////////////////////////////////////

	groupSocket = new QGroupBox(tabSock, "groupSocket");
	groupSocket->setGeometry(0,0, 355, 150 );
	groupSocket->setTitle("Ip Table");

	ipTable = new XListView(groupSocket);
	ipTable->setGeometry(10, 20, 335, 125);

    
    resize( QSize(362, 217).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );



}

/*
 *  Destroys the object and frees any allocated resources
 */
XBotLauncherDialogBase::~XBotLauncherDialogBase()
{
    // no need to delete child widgets, Qt does it all for us
}

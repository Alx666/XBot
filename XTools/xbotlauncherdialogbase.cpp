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

	//PERSONALIZATION
	setCaption("XTools v1.0");
	//setCaption("XTools v1.0, licensed To: <eXø>::Rîñø");
	//setCaption("XTools v1.0, licensed To: Troy");
	

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
	tabKeys = new QWidget( tabWidget, "tabKeys" );
	tabSock = new QWidget(tabWidget, "tabSock");

	tabWidget->insertTab( tabPath, QString("XPath")   );
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


    pbChoose = new QPushButton( tabPath, "pbChoose" );
	pbChoose->setText("...");
    pbChoose->setGeometry( QRect( 320, 29, 30, 22 ) );



	//Create Components and insert them in the XConfig tab
	///////////////////////////////////////////////////////

	//Toggle Keys
    groupToggleKeys = new QGroupBox( tabKeys, "groupToggleKeys" );
    groupToggleKeys->setGeometry( QRect( 0, 0, 220, 150 ) );
	groupToggleKeys->setTitle("Quick Keys");

    QWidget* privateLayoutWidget_2 = new QWidget( groupToggleKeys, "layGridToggleKeys" );
    privateLayoutWidget_2->setGeometry( QRect( 10, 15, 155, 120 ) );
    layGridToggleKeys = new QGridLayout( privateLayoutWidget_2, 1, 1, 11, 3, "layGridToggleKeys"); 

	leMasterSwitch = new LineEditEx( privateLayoutWidget_2, "leMasterSwitch");
	layGridToggleKeys->addWidget( leMasterSwitch, 0, 1 );
    labelMasterSwitch = new QLabel( privateLayoutWidget_2, "labelMasterSwitch" );
	labelMasterSwitch->setText("Master Switch:");
    layGridToggleKeys->addWidget( labelMasterSwitch, 0, 0 );
    
	leDodge = new LineEditEx( privateLayoutWidget_2, "leDodge");
    layGridToggleKeys->addWidget( leDodge, 1, 1 );
    labelDodge = new QLabel( privateLayoutWidget_2, "labelDodge" );
	labelDodge->setText("Dodge bind:");
    layGridToggleKeys->addWidget( labelDodge, 1, 0 );

 
	//TIMERS
/*
	groupTimers = new QGroupBox( tabKeys, "groupTimers");
	groupTimers->setGeometry( QRect(172, 0 , 180, 150 ) );
	groupTimers->setTitle("Timers Keys");
*/
	leResetShield  = new LineEditEx( privateLayoutWidget_2, "leResetShield");
	layGridToggleKeys->addWidget( leResetShield, 2, 1 );
	labelResetShield = new QLabel( privateLayoutWidget_2, "labelResetShield" );
	labelResetShield->setText("Timer Shield:");
	layGridToggleKeys->addWidget( labelResetShield, 2, 0 );

	leResetDDamage = new LineEditEx( privateLayoutWidget_2, "leResetDDamage");
	layGridToggleKeys->addWidget( leResetDDamage, 3, 1 );
	labelResetDDamage = new QLabel( privateLayoutWidget_2, "labelResetDDamage" );
	labelResetDDamage->setText("Timer DDamage:");
	layGridToggleKeys->addWidget( labelResetDDamage, 3, 0 );


	leResetRedeem  = new LineEditEx( privateLayoutWidget_2, "leResetRedeem");
	layGridToggleKeys->addWidget( leResetRedeem, 4, 1 );
	labelResetRedeem = new QLabel( privateLayoutWidget_2, "labelResetRedeem" );
	labelResetRedeem->setText("Timer Redeem:");
	layGridToggleKeys->addWidget( labelResetRedeem, 4, 0 );


	leMasterSwitch->setBuddy(leDodge);
	leDodge->setBuddy(leResetShield);
	leResetShield->setBuddy(leResetDDamage);
	leResetDDamage->setBuddy(leResetRedeem);
	leResetRedeem->setBuddy(leMasterSwitch);
	
	

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

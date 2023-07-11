/****************************************************************************
** Form interface generated from reading ui file '.\xbotlauncherdialogbase.ui'
**
** Created: lun 28. giu 02:25:17 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.3   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef XBOTLAUNCHERDIALOGBASE_H
#define XBOTLAUNCHERDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlistview.h>
#include <QComboBox.h>
#include "XGlLogo.h"


class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QTabWidget;
class QWidget;
class LineEditEx;
class QLabel;
class QGroupBox;
class QSlider;
class XListView;
class XLCDNumber;

class XBotLauncherDialogBase : public QDialog
{
    Q_OBJECT

public:
    XBotLauncherDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~XBotLauncherDialogBase();

    QPushButton* pbLaunch;
    QPushButton* pbCancel;
	QPushButton* pbChoose;
	QPushButton* pbDefault;
	QPushButton* pbEdit;

    QTabWidget* tabWidget;
    QWidget* tabPath;
	QWidget* tabKeys;
	QWidget* tabSock;

	XGlLogo* xbotLogo;

	QLineEdit* lePathToUT;
	QLineEdit* leExeParam;

    LineEditEx* leDodge;
	LineEditEx* leMasterSwitch;
	LineEditEx* leResetShield;
	LineEditEx* leResetDDamage;
	LineEditEx* leResetRedeem;


	QGroupBox* groupToggleKeys;
	QGroupBox* groupMenuKeys;
	QGroupBox* groupGameKeys;
	QGroupBox* groupMouseSpeed;
	QGroupBox* groupTimers;
	QGroupBox* groupSocket;


    QLabel* labelDodge;
    QLabel* labelPath;
	QLabel* labelParam;
	QLabel* labelMasterSwitch;
	QLabel* labelResetShield;
	QLabel* labelResetRedeem;
	QLabel* labelResetDDamage;

	XListView* ipTable;

protected:
    QGridLayout* layGridToggleKeys;
    QGridLayout* layGridMenuKeys;
};

#endif // XBOTLAUNCHERDIALOGBASE_H

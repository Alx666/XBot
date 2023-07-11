#include "xbotlauncherdialogbase.h"
#include "XConfig.h"
#include <qslider.h>

class XBotLauncherDialog : public XBotLauncherDialogBase
{
	Q_OBJECT
public:
	XBotLauncherDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags f = 0);

	XConfig *xconfig;
	bool configChanged;

public slots:
	void slotBuildDefault();
	void slotStart();
	void slotSaveConfig();
	void slotChoosePath();
	void slotQuit();
};


#include <qapplication.h>
#include "xbotlauncherdialog.h"

int main( int argc, char** argv )
{
	QApplication app( argc, argv );

	XBotLauncherDialog dialog( 0, 0, TRUE );
	app.setMainWidget(&dialog);

	dialog.exec();

	return 0;
}


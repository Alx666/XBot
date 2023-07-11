#pragma once

#include <qlistview.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include "XConfig.h"

#define MAX_ELEMENTS 32

class XListView : public QListView
{
	Q_OBJECT
public:
	XListView(QWidget* parent = 0, const char* name = 0, WFlags f = 0);
	~XListView();

	bool add(XPlayer player);
	static unsigned int checkAndConvert(QString &txtip);
	static QString idToIp(unsigned int codedIp);

public slots:
	void slotEditItem();
	void slotDeleteItem();
	void slotAddItem();



private:

	void contextMenuEvent(QContextMenuEvent *);
	QPtrList<QListViewItem> lstPlayer;
};

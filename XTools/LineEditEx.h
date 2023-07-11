#pragma once

#include <qlineedit.h>
#include <qlcdnumber.h> 
#include <windows.h>
#include <qlcdnumber.h>

struct keycodemap_t
{
	unsigned int keycode;
	QString name;
};


class LineEditEx : public QLineEdit
{
	Q_OBJECT

public:
	LineEditEx(QWidget *parent, const char *name, LineEditEx *buddy = 0, bool keyboardOnly = false);
	~LineEditEx();
	keycodemap_t key;
	//int key;
	void setKey(int keyToSet);
	void setBuddy(LineEditEx* buddy);
	int getKey();

	LineEditEx* nearBuddy;

private:
	bool keybOnly;
	void convertToWin32(int qtKey);
	void interpretAsWin32(int keyToSet);
	void keyPressEvent(QKeyEvent *e); 
	void mouseDoubleClickEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);

	void focusBuddy();
};

class XLCDNumber : public QLCDNumber
{
	Q_OBJECT
public:
	XLCDNumber(unsigned int numDigits, QWidget* parent = 0, const char* name = 0) : QLCDNumber(numDigits, parent, name) {};

public slots:
	void display(int n)
	{
		double d = n/4.0;
		QString v;
		v.setNum(d, 'f', 2);
		QLCDNumber::display(v);
	}


};
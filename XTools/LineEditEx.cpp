#include "LineEditEx.h"
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"


//DEBUG INCLUDE
#include <qmessagebox.h>



LineEditEx::LineEditEx(QWidget *parent, const char *name, LineEditEx *buddy, bool keyboardOnly)
	: QLineEdit(parent, name)
{
	key.keycode = 0;		
	key.name = "";
	setPaletteBackgroundColor(QColor(190, 190, 190));
	//setFrameShape(QFrame::WinPanel);
	//setFrameShadow(QFrame::Plain);
	nearBuddy =  buddy;
	//setDisabled(true);
	keybOnly = keyboardOnly;
}

void LineEditEx::focusBuddy()
{
	if(nearBuddy == 0)
		return;

	nearBuddy->setFocus();
	nearBuddy->selectAll();
}

void LineEditEx::setBuddy(LineEditEx* buddy)
{
	nearBuddy = buddy;
}

LineEditEx::~LineEditEx()
{
}

void LineEditEx::keyPressEvent(QKeyEvent *e)
{
	convertToWin32(e->key());
	setText(key.name);
	focusBuddy();
}

void LineEditEx::mouseDoubleClickEvent(QMouseEvent *e)
{
	if(keybOnly)
	{
		QMessageBox::information(this, "Information", "This must be Keyboard!");
		return;
	}

	if(e->button() != Qt::LeftButton)
		return;

	convertToWin32(e->button());
	setText(key.name);
	focusBuddy();
}

void LineEditEx::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
		return;

	if(keybOnly)
	{
		QMessageBox::information(this, "Information", "This must be Keyboard!");
		return;
	}

	//QString v = *new QString();
	//QMessageBox::information(this, "value", v.setNum(e->button()));

	convertToWin32(e->button());
	setText(key.name);
	focusBuddy();
}

void LineEditEx::setKey(int keyToSet)
{
	interpretAsWin32(keyToSet);
	setText(key.name);
}

int LineEditEx::getKey()
{
	return key.keycode;
}


//Interpreta i valori caricati da .INI come Key windows
void LineEditEx::interpretAsWin32(int keyToSet)
{
	switch(keyToSet)
	{
	case VK_LBUTTON:	key.name = QString("MB1");		break;
	case VK_RBUTTON:	key.name = QString("MB2");		break;
	case VK_MBUTTON:	key.name = QString("MB3");		break;
	case VK_SHIFT:		key.name = QString("SHIFT");		break;
	case VK_CONTROL:	key.name = QString("CTRL ");		break;
	//case VK_LWIN:		key.name = QString("VK_LWIN");		break;
	case VK_MENU:		key.name = QString("ALT");		break;
	//case VK_CAPITAL:	key.name = QString("VK_CAPITAL");	break;
	case VK_SPACE:		key.name = QString("SPACE");		break;
	case VK_F1:			key.name = QString("F1");			break;
	case VK_F2:			key.name = QString("F2");			break;
	case VK_F3:			key.name = QString("F3");			break;
	case VK_F4:			key.name = QString("F4");			break;
	case VK_F5:			key.name = QString("F5");			break;
	case VK_F6:			key.name = QString("F6");			break;
	case VK_F7:			key.name = QString("F7");			break;
	case VK_F8:			key.name = QString("F8");			break;
	case VK_F9:			key.name = QString("F9");			break;
	case VK_F10:		key.name = QString("F10");			break;
	case VK_F11:		key.name = QString("F11");			break;
	case VK_F12:		key.name = QString("F12");			break;
	case VK_INSERT:		key.name = QString("INS");		break;
	case VK_HOME:		key.name = QString("HOME");			break;
	case VK_DELETE:		key.name = QString("DEL");		break;
	case VK_END:		key.name = QString("END");			break;
	case VK_PRIOR:		key.name = QString("PRIOR");		break;
	case VK_NEXT:		key.name = QString("NEXT");			break;
	case VK_LEFT:		key.name = QString("LEFT");			break;
	case VK_UP:			key.name = QString("UP");			break;
	case VK_RIGHT:		key.name = QString("RIGHT");		break;
	case VK_DOWN:		key.name = QString("DOWN");			break;
	case VK_NUMPAD0:	key.name = QString("NUM0");			break;
	case VK_NUMPAD1:	key.name = QString("NUM1");			break;
	case VK_NUMPAD2:	key.name = QString("NUM2");			break;
	case VK_NUMPAD3:	key.name = QString("NUM3");			break;
	case VK_NUMPAD4:	key.name = QString("NUM4");			break;
	case VK_NUMPAD5:	key.name = QString("NUM5");			break;
	case VK_NUMPAD6:	key.name = QString("NUM6");			break;
	case VK_NUMPAD7:	key.name = QString("NUM7");			break;
	case VK_NUMPAD8:	key.name = QString("NUM8");			break;
	case VK_NUMPAD9:	key.name = QString("NUM9");			break;
	case VK_MULTIPLY:	key.name = QString("*");			break;
	case VK_ADD:		key.name = QString("+");			break;
	case VK_SUBTRACT:	key.name = QString("-");			break;
	case VK_DIVIDE: 	key.name = QString("/");			break;
	case VK_DECIMAL:	key.name = QString(".");			break;
	case VK_RETURN:		key.name = QString("RETURN");		break;
	//case VK_NUMLOCK	key.name = QString("VK_NUMLOCK");	break;
	//case VK_SCROLL:	key.name = QString("VK_SCROLL");	break;
	//case VK_PAUSE:	key.name = QString("VK_PAUSE");		break;
	//case VK_ESCAPE:	key.name = QString("VK_ESCAPE");	break;
	default: key.name = QString(QChar(keyToSet));
	}

	key.keycode = keyToSet;
}


//Converte le costanti delle VirtualKey QT in costanti Windows
void LineEditEx::convertToWin32(int qtKey)
{
	switch(qtKey)
	{
	case    1: key.keycode = VK_LBUTTON;	key.name = QString("MB1");	break; //VK_LBUTTON
	case    2: key.keycode = VK_RBUTTON;	key.name = QString("MB2");	break; //VK_RBUTTON
	case    4: key.keycode = VK_MBUTTON;	key.name = QString("MB3");	break; //VK_MBUTTON
	case 4128: key.keycode = VK_SHIFT;		key.name = QString("SHIFT");	break;
	case 4129: key.keycode = VK_CONTROL;	key.name = QString("CTRL ");	break;
	case 4131: key.keycode = VK_MENU	;	key.name = QString("ALT ");		break; //Corregge incongruenza QT => WIN
//  case 4130: key.keycode = VK_LWIN;		key.name = QString("LWIN");		break;
//	case 4181: key.keycode = VK_MENU ;		key.name = QString("MENU");		break;
//	case 4132: key.keycode = VK_CAPITAL;	key.name = QString("CAPITAL");	break;
	case   32: key.keycode = VK_SPACE;		key.name = QString("SPACE");	break;
	case 4144: key.keycode = VK_F1;			key.name = QString("F1");		break;
	case 4145: key.keycode = VK_F2;			key.name = QString("F2");		break;
	case 4146: key.keycode = VK_F3;			key.name = QString("F3");		break;
	case 4147: key.keycode = VK_F4;			key.name = QString("F4");		break;
	case 4148: key.keycode = VK_F5;			key.name = QString("F5");		break;
	case 4149: key.keycode = VK_F6;			key.name = QString("F6");		break;
	case 4150: key.keycode = VK_F7;			key.name = QString("F7");		break;
	case 4151: key.keycode = VK_F8;			key.name = QString("F8");		break;
	case 4152: key.keycode = VK_F9;			key.name = QString("F9");		break;
	case 4153: key.keycode = VK_F10;		key.name = QString("F10");		break;
	case 4154: key.keycode = VK_F11;		key.name = QString("F11");		break;
	case 4155: key.keycode = VK_F12;		key.name = QString("F12");		break;
	case 4102: key.keycode = VK_INSERT;		key.name = QString("INS");		break;
	case 4112: key.keycode = VK_HOME;		key.name = QString("HOME");		break;
	case 4103: key.keycode = VK_DELETE;		key.name = QString("DEL");		break;
	case 4113: key.keycode = VK_END;		key.name = QString("END");		break;
	case 4118: key.keycode = VK_PRIOR;		key.name = QString("PRIOR");	break;
	case 4119: key.keycode = VK_NEXT;		key.name = QString("NEXT");		break;
	case 4114: key.keycode = VK_LEFT;		key.name = QString("LEFT");		break;
	case 4115: key.keycode = VK_UP;			key.name = QString("UP");		break;
	case 4116: key.keycode = VK_RIGHT;		key.name = QString("RIGHT");	break;
	case 4117: key.keycode = VK_DOWN;		key.name = QString("DOWN");		break;
	case   48: key.keycode = VK_NUMPAD0;	key.name = QString("NUM0");		break;
	case   49: key.keycode = VK_NUMPAD1;	key.name = QString("NUM1");		break;
	case   50: key.keycode = VK_NUMPAD2;	key.name = QString("NUM2");		break;
	case   51: key.keycode = VK_NUMPAD3;	key.name = QString("NUM3");		break;
	case   52: key.keycode = VK_NUMPAD4;	key.name = QString("NUM4");		break;
	case   53: key.keycode = VK_NUMPAD5;	key.name = QString("NUM5");		break;
	case   54: key.keycode = VK_NUMPAD6;	key.name = QString("NUM6");		break;
	case   55: key.keycode = VK_NUMPAD7;	key.name = QString("NUM7");		break;
	case   56: key.keycode = VK_NUMPAD8;	key.name = QString("NUM8");		break;
	case   57: key.keycode = VK_NUMPAD9;	key.name = QString("NUM9");		break;
	case   42: key.keycode = VK_MULTIPLY;	key.name = QString("*");		break;
	case   43: key.keycode = VK_ADD;		key.name = QString("+");		break;
	case   45: key.keycode = VK_SUBTRACT;	key.name = QString("-");		break;
	case   47: key.keycode = VK_DIVIDE;		key.name = QString("/");		break;
	case   46: key.keycode = VK_DECIMAL;	key.name = QString(".");		break;
	case 4100: key.keycode = VK_RETURN;		key.name = QString("ENTER");	break;
//  case 1025: key.keycode = VK_NUMLOCK;	key.name = QString("NUMLOCK");	break;
//	case 4100: key.keycode = VK_RETURN;		key.name = QString("RETURN");	break;
//	case 4134: key.keycode = VK_SCROLL;		key.name = QString("SCROLL");	break;
//  case 4104: key.keycode = VK_PAUSE;		key.name = QString("PAUSE");	break;
//  case 4096: key.keycode = VK_ESCAPE;		key.name = QString("ESCAPE");	break;
	default:   key.keycode = qtKey;			key.name = QString(QChar(key.keycode));
	}

}

#include "XListView.h"
#include <qpopupmenu.h>
#include <qlabel.h>
#include <qcursor.h>

XListView::XListView(QWidget* parent, const char* name, WFlags f) : QListView(parent, name, f)
{
	addColumn("Player name:");
	addColumn("Ip Address:");
	setSelectionMode(QListView::Single);
}


XListView::~XListView()
{
}

void XListView::slotDeleteItem()
{
	QListViewItem *current = selectedItem();
	
	QListViewItemIterator it(current);
	lstPlayer.remove(it.current());
	delete current;
	current = 0;
}

void XListView::slotEditItem()
{
	QListViewItem *current = selectedItem();

	bool ok;
	QString playername = QInputDialog::getText("XSocket", "Enter player name:", QLineEdit::Normal, current->text(0), &ok, this);
	if(ok && !playername.isEmpty() && playername.length() < 128)
	{
		ok = false;
		QString address = QInputDialog::getText("XSocket", "Enter player ip:", QLineEdit::Normal, current->text(1), &ok, this);

		if(ok && !address.isEmpty())
		{
			if(checkAndConvert(address) == 0)
			{
				QMessageBox::warning(this, "Error", "Invalid Ip address");
				return;
			}

			QListViewItemIterator it(current);
			lstPlayer.remove(it.current());
			delete current;
			current = 0;

			lstPlayer.append(new QListViewItem(this, playername, address));
		}
	}
}

void XListView::slotAddItem()
{
	bool ok;
	QString playername = QInputDialog::getText("XSocket", "Enter player name:", QLineEdit::Normal, QString::null, &ok, this);
	if(ok && !playername.isEmpty() && playername.length() < 128)
	{
		ok = false;
		QString address = QInputDialog::getText("XSocket", "Enter player ip:", QLineEdit::Normal, QString::null, &ok, this);

		if(ok && !address.isEmpty())
		{
			if(checkAndConvert(address) == 0)
			{
				QMessageBox::warning(this, "Error", "Invalid Ip address");
				return;
			}

			lstPlayer.append(new QListViewItem(this, playername, address));
		}
	}
}


void XListView::contextMenuEvent(QContextMenuEvent *e)
{
    QPopupMenu*	contextMenu = new QPopupMenu( this );
    Q_CHECK_PTR( contextMenu );
    QLabel *caption = new QLabel( "<font color=darkblue><u><b>"
	"Edit Menu</b></u></font>", this );
    caption->setAlignment( Qt::AlignCenter );
    contextMenu->insertItem( caption );
    contextMenu->insertItem( "&Add...",  this, SLOT(slotAddItem()));
    contextMenu->insertItem( "&Edit...", this, SLOT(slotEditItem()));
    contextMenu->insertItem( "&Remove", this, SLOT(slotDeleteItem()));
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}

unsigned int XListView::checkAndConvert(QString &txtip)
{
	QString sNum1 = txtip.section('.', 0, 0);
	QString sNum2 = txtip.section('.', 1, 1);
	QString sNum3 = txtip.section('.', 2, 2);
	QString sNum4 = txtip.section('.', 3, 3);

	if(sNum1.isNull() || sNum2.isNull() || sNum3.isNull() || sNum4.isNull())
		return 0;

	int n1,n2,n3,n4;
	bool ok1, ok2, ok3, ok4;

	n1 = sNum1.toInt(&ok1);
	n2 = sNum2.toInt(&ok2);
	n3 = sNum3.toInt(&ok3);
	n4 = sNum4.toInt(&ok4);

	if(!ok1 || !ok2 || !ok3 || !ok4)
		return 0;

	if(n1 < 0 || n2 < 0 || n3 < 0 || n4 < 0 || n1 > 255 || n2 > 255 || n3 > 255 || n4 > 255)
		return 0;



	QString s1, s2, s3, s4;
	s1.setNum(n1);s2.setNum(n2);s3.setNum(n3);s4.setNum(n4);

	txtip = s1+"."+s2+"."+s3+"."+s4; //Ip to be show in the list

	unsigned int result;
	unsigned char* ptr = (unsigned char*)&result;
	ptr[0] = n1;
	ptr[1] = n2;
	ptr[2] = n3;
	ptr[3] = n4;
	
	return result;
}

QString XListView::idToIp(unsigned int codedIp)
{
	unsigned char* ptr = (unsigned char*)&codedIp;
	unsigned int n1 = ptr[0];
	unsigned int n2 = ptr[1];
	unsigned int n3 = ptr[2];
	unsigned int n4 = ptr[3];

	QString s1,s2,s3,s4,ip;
	
	s1.setNum(n1);
	s2.setNum(n2);
	s3.setNum(n3);
	s4.setNum(n4);
	ip = s1+"."+s2+"."+s3+"."+s4;

	return ip;
}


bool XListView::add(XPlayer player)
{
	if(player.name == 0)
		return false;

	QString playername = player.name;
	if(!playername.isEmpty())
	{
		QString address = XListView::idToIp(player.codedIp);

		if(!address.isEmpty())
		{
			if(checkAndConvert(address) == 0)
			{
				QMessageBox::warning(this, "Error", "Invalid id from ini file!");
				return true;
			}

			lstPlayer.append(new QListViewItem(this, playername, address));
		}
	}
	return true;
}


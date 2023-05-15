#include "add_classdlg.h"

add_ClassDlg::add_ClassDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.ok_Button, SIGNAL(clicked()), this, SLOT(ok_button()));
}

add_ClassDlg::~add_ClassDlg()
{

}

void add_ClassDlg::ok_button()
{
	QString classnumber = ui.CLNOEdit->text();
	QString classname = ui.CLNameEdit->text();
	QString acno = ui.ACNOEdit->text();
	emit signaInfo(classnumber, classname, acno.toInt());
	//qDebug() << stunumber << " " << stuname << " " << stusex;
	//ui.stuNumEdit->setEnabled(true);
}

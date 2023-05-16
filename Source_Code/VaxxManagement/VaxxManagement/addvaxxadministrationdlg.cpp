#include "addcoursedlg.h"

addcoursedlg::addcoursedlg(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_button()));
}

addcoursedlg::~addcoursedlg()
{
	
}

void addcoursedlg::ok_button()
{
	QString cno = ui.cno_lineEdit->text();
	QString tno = ui.cno_lineEdit->text();
	QString cname = ui.cname_lineEdit->text();
	QString cre = ui.cre_lineEdit->text();
	QString ctime = ui.ctime_lineEdit->text();
	QString ctype = ui.ctype_lineEdit->text();

	emit signalInfo(cno,tno,cname,cre.toFloat(),ctime.toInt(),ctype);
	ui.cno_lineEdit->setEnabled(true);
}


#include "add_scoredlg.h"

add_ScoreDlg::add_ScoreDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_button()));
}

add_ScoreDlg::~add_ScoreDlg()
{

}

void add_ScoreDlg::ok_button()
{
	QString sno = ui.sno_Edit->text();
	QString cno = ui.cno_Edit->text();
	QString f1 = ui.fscore_Edit->text();//�����ɼ�
	QString f2 = ui.sscore_Edit->text();//�����ɼ�
	QString f3 = ui.tscore_Edit->text();//���޳ɼ�
	emit signaInfo(sno.toInt(), cno, f1.toFloat(),f2.toFloat(),f3.toFloat());
	//qDebug() << stunumber << " " << stuname << " " << stusex;
	//ui.stuNumEdit->setEnabled(true);
}
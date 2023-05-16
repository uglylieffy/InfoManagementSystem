#include "add_teacherdlg.h"

add_TeacherDlg::add_TeacherDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_button()));
}

add_TeacherDlg::~add_TeacherDlg()
{

}

void add_TeacherDlg::ok_button()
{
	QString tno= ui.tno_Edit->text();
	QString tname = ui.tname_Edit->text();
	QString age = ui.age_Edit->text();
	QString sex = ui.sex_Edit->text();
	QString pos = ui.pos_Edit->text();
	emit signalStuInfo(tno, tname,age.toInt(),sex, pos);
	
}


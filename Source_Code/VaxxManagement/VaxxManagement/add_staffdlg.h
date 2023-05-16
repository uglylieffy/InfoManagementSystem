#ifndef ADD_TEACHERDLG_H
#define ADD_TEACHERDLG_H

#include <QDialog>
#include "ui_add_teacherdlg.h"

class add_TeacherDlg : public QDialog
{
	Q_OBJECT

public:
	add_TeacherDlg(QWidget *parent = 0);
	~add_TeacherDlg();

private:
	Ui::add_TeacherDlg ui;

private slots:
	void ok_button();

signals:
	void signalStuInfo(QString, QString,int, QString,QString);
};

#endif // ADD_TEACHERDLG_H

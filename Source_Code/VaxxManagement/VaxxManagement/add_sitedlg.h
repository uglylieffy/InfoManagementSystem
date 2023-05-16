#ifndef ADD_CLASSDLG_H
#define ADD_CLASSDLG_H

#include <QDialog>
#include "ui_add_classdlg.h"

class add_ClassDlg : public QDialog
{
	Q_OBJECT

public:
	add_ClassDlg(QWidget *parent = 0);
	~add_ClassDlg();

private:
	Ui::add_ClassDlg ui;

private slots:
	void ok_button();

signals:
	void signaInfo(QString, QString, int);
};

#endif // ADD_CLASSDLG_H

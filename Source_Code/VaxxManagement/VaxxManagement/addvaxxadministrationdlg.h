#ifndef ADDCOURSEDLG_H
#define ADDCOURSEDLG_H

#include <QWidget>
#include "ui_addcoursedlg.h"

namespace Ui{
	class addcoursedlg;
}

class addcoursedlg : public QWidget
{
	Q_OBJECT

public:
	addcoursedlg(QWidget *parent = 0);
	~addcoursedlg();

private slots:
	void ok_button();

signals:
	void signalInfo(QString, QString, QString,float,int,QString);


private:
	Ui::addcoursedlg ui;
};

#endif // ADDCOURSEDLG_H

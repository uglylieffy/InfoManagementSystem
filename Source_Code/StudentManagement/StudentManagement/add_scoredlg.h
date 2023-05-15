#ifndef ADD_SCOREDLG_H
#define ADD_SCOREDLG_H

#include <QDialog>
#include "ui_add_scoredlg.h"

class add_ScoreDlg : public QDialog
{
	Q_OBJECT

public:
	add_ScoreDlg(QWidget *parent = 0);
	~add_ScoreDlg();

private:
	Ui::add_ScoreDlg ui;

private slots:
	void ok_button();

signals:
	void signaInfo(int, QString, float,float,float);

};

#endif // ADD_SCOREDLG_H

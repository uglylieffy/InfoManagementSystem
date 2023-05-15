#include "addstudlg.h"
#include "ui_addstudlg.h"
#include <QDateTime>
#include <QStringList>
#include <QString>
#include <QDebug>


addStudlg::addStudlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStudlg)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this,SLOT(ok_button()));
}

addStudlg::~addStudlg()
{
    delete ui;
}

void addStudlg::ok_button()
{
    QString stunumber=ui->stuNumEdit->text();
    QString stuname=ui->stuNameEdit->text();
	QString stusex = ui->stuSexEdit->text();
	QString stuage = ui->stuAgeEdit->text();
	QString stuclno = ui->stuClnoEdit->text();
	emit signalStuInfo(stunumber.toInt(), stuname, stusex,stuage.toInt(),stuclno);
	qDebug() << stunumber << " " << stuname << " " << stusex;
    ui->stuNumEdit->setEnabled(true);
}

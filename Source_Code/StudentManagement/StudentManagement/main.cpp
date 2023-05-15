#include "mainwindow.h"
#include <QApplication>
#include<QSqlDatabase>
#include<QSqlError>
#include<QMessageBox>
#include <QDebug>

void OpenDatabase()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName(QString("DRIVER={SQL SERVER};"
		"SERVER=%1;" //服务器名称
		"DATABASE=%2;"//数据库名
		"UID=%3;"           //登录名
		"PWD=%4;"        //密码
		).arg("LAPTOP-JAIVV4H5")
		.arg("stuManagement")
		.arg("sa")
		.arg("123456")
		);
	if (!db.open())
	{
		QMessageBox::critical(0, qApp->tr("Cannot open database"),
			db.lastError().databaseText(), QMessageBox::Cancel);
	}
}

int main(int argc, char *argv[])
{
	OpenDatabase();
	QApplication a(argc, argv);

	mainwindow *w = new mainwindow();

	w->show();

	return a.exec();
}

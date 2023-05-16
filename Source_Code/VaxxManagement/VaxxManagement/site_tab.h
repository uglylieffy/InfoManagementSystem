#pragma execution_character_set("utf-8")
#ifndef CLASS_TAB_H
#define CLASS_TAB_H

#include <QWidget>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include "ui_class_tab.h"
#include<QMessageBox>
#include<QString>
#include<QSqlQuery>
#include<QSqlError>
#include"add_ClassDlg.h"

class class_tab : public QWidget
{
	Q_OBJECT

public:
	class_tab(QWidget *parent = 0);
	~class_tab();

private:
	Ui::class_tab ui;
	QSqlQueryModel *model;
	QSqlTableModel *model2;
	add_ClassDlg *m_pAddcla;
	QString name, num;

private slots:
	void fresh_slot();	//点击 刷新 按钮后执行查询全表的槽函数
	void onBtnFind();		//点击查询后的槽函数
	void onBtnDel();    //删除的槽函数
	void onBtnMod();	//点击修改的槽函数
	void onBtnSubmit();	//点击提交修改的槽函数
	void onBtnRollback();//点击撤回修改的槽函数
	void onBtnAdd();		//点击 添加 按钮后的要执行的槽函数
	void ExecAddSql(QString nom, QString name,int acno);
	//班级表中接收完添加信息后  要执行的槽函数

};

#endif // CLASS_TAB_H

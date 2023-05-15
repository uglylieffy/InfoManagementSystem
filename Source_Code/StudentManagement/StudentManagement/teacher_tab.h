#pragma execution_character_set("utf-8")

#ifndef TEACHER_TAB_H
#define TEACHER_TAB_H


#include "ui_teacher_tab.h"
#include"add_TeacherDlg.h"
#include <QWidget>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QString>
#include<QSqlQuery>
#include<QSqlError>

class teacher_tab : public QWidget
{
	Q_OBJECT

public:
	teacher_tab(QWidget *parent = 0);
	~teacher_tab();

private:
	Ui::teacher_tab ui;
	QSqlQueryModel *model;
	QSqlTableModel *model2;
	add_TeacherDlg *m_pAddTeacher;
	QString name,num;
	 

private slots:
	void fresh_slot();			//点击 刷新 按钮后执行查询全表的槽函数
	void onBtnAdd();		//点击 添加 按钮后的要执行的槽函数
	void onBtnFind();		//点击查询后的槽函数
	void onBtnDel();    //删除的槽函数
	void ExecAddSql(int num, QString name, QString sex, int age, QString clno);
	//学生表中接收完添加信息后  要执行的槽函数
	void onBtnMod();	//点击修改的槽函数
	void onBtnSubmit();	//点击提交修改的槽函数
	void onBtnRollback();//点击撤回修改的槽函数
};

#endif // TEACHER_TAB_H

#ifndef COURSE_TAB_H
#define COURSE_TAB_H

#include <QWidget>
#include "ui_course_tab.h"
#include"addcoursedlg.h"
#include<QSqlQueryModel>
#include<qsqltablemodel.h>
#include<QSqlQuery>
#include<QMessageBox>
#include<QString>
#include<qsqlerror.h>


class course_tab : public QWidget
{
	Q_OBJECT

public:
	course_tab(QWidget *parent = 0);
	~course_tab();

private:
	Ui::course_tab ui;
	QSqlQueryModel *model;
	QSqlTableModel *model2;
	addcoursedlg *m_pAddCourseDlg;
	QString name, num;

private slots:
	void fresh_slot();			//点击 刷新 按钮后执行查询全表的槽函数
	void onBtnFind();
	void onBtnDel();			//点击删除的槽函数
	void onBtnAdd();
	void onBtnMod();	//点击修改的槽函数
	void onBtnSubmit();	//点击提交修改的槽函数
	void onBtnRollback();//点击撤回修改的槽函数
	void ExecAddSql(QString cno, QString tno, QString cname,float cre,int ctime,QString ctype);
};

#endif // COURSE_TAB_H

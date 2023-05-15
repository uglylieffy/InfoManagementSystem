#ifndef SCORE_TAB_H
#define SCORE_TAB_H

#include "ui_score_tab.h"
#include"add_ScoreDlg.h"
#include <QWidget>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QString>
#include<QSqlQuery>
#include<QSqlError>

class score_tab : public QWidget
{
	Q_OBJECT

public:
	score_tab(QWidget *parent = 0);
	~score_tab();

private:
	Ui::score_tab ui;
	add_ScoreDlg *m_pAddScore;
	QSqlQueryModel *model;
	QSqlTableModel *model2;
	QString name;
	int num;

private slots:
	void fresh_slot();			//点击 刷新 按钮后执行查询全表的槽函数
	void onBtnFind();		//点击查询后的槽函数
	void onBtnDel();    //删除的槽函数
	void onBtnMod();	//点击修改的槽函数
	void onBtnSubmit();	//点击提交修改的槽函数
	void onBtnRollback();//点击撤回修改的槽函数
	void onBtnAdd();		//点击 添加 按钮后的要执行的槽函数
	void ExecAddSql(int sno, QString cno, float f1,float f2,float f3);
	//班级表中接收完添加信息后  要执行的槽函数
};

#endif // SCORE_TAB_H

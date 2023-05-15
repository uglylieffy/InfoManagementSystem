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
	void fresh_slot();			//��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳۺ���
	void onBtnAdd();		//��� ��� ��ť���Ҫִ�еĲۺ���
	void onBtnFind();		//�����ѯ��Ĳۺ���
	void onBtnDel();    //ɾ���Ĳۺ���
	void ExecAddSql(int num, QString name, QString sex, int age, QString clno);
	//ѧ�����н����������Ϣ��  Ҫִ�еĲۺ���
	void onBtnMod();	//����޸ĵĲۺ���
	void onBtnSubmit();	//����ύ�޸ĵĲۺ���
	void onBtnRollback();//��������޸ĵĲۺ���
};

#endif // TEACHER_TAB_H

#ifndef STU_TAB_H
#define STU_TAB_H

#include "ui_stu_tab.h"
#include"addstudlg.h"
#include <QWidget>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QString>
#include<QSqlQuery>
#include<QSqlError>

class stu_tab : public QWidget
{
	Q_OBJECT

public:
	stu_tab(QWidget *parent = 0);
	~stu_tab();

private:
	Ui::stu_tab ui;
	QSqlQueryModel *model;
	QSqlTableModel *model2;
	addStudlg *m_pAddStuDlg;
	QString name;
	int num;

private slots:
	void fresh_slot();			//��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳۺ���
	void onBtnAdd();		//��� ��� ��ť���Ҫִ�еĲۺ���
	void onBtnFind();		//�����ѯ��Ĳۺ���
	void onBtnDel();    //ɾ���Ĳۺ���
	void ExecAddSql(int num, QString name, QString sex,int age,QString clno);
													//ѧ�����н����������Ϣ��  Ҫִ�еĲۺ���
	void onBtnMod();	//����޸ĵĲۺ���
	void onBtnSubmit();	//����ύ�޸ĵĲۺ���
	void onBtnRollback();//��������޸ĵĲۺ���
};

#endif // STU_TAB_H

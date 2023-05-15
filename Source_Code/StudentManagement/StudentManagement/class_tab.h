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
	void fresh_slot();	//��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳۺ���
	void onBtnFind();		//�����ѯ��Ĳۺ���
	void onBtnDel();    //ɾ���Ĳۺ���
	void onBtnMod();	//����޸ĵĲۺ���
	void onBtnSubmit();	//����ύ�޸ĵĲۺ���
	void onBtnRollback();//��������޸ĵĲۺ���
	void onBtnAdd();		//��� ��� ��ť���Ҫִ�еĲۺ���
	void ExecAddSql(QString nom, QString name,int acno);
	//�༶���н����������Ϣ��  Ҫִ�еĲۺ���

};

#endif // CLASS_TAB_H

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
	void fresh_slot();			//��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳۺ���
	void onBtnFind();
	void onBtnDel();			//���ɾ���Ĳۺ���
	void onBtnAdd();
	void onBtnMod();	//����޸ĵĲۺ���
	void onBtnSubmit();	//����ύ�޸ĵĲۺ���
	void onBtnRollback();//��������޸ĵĲۺ���
	void ExecAddSql(QString cno, QString tno, QString cname,float cre,int ctime,QString ctype);
};

#endif // COURSE_TAB_H

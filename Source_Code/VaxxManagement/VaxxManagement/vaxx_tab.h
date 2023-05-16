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
	void fresh_slot();			//��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳۺ���
	void onBtnFind();		//�����ѯ��Ĳۺ���
	void onBtnDel();    //ɾ���Ĳۺ���
	void onBtnMod();	//����޸ĵĲۺ���
	void onBtnSubmit();	//����ύ�޸ĵĲۺ���
	void onBtnRollback();//��������޸ĵĲۺ���
	void onBtnAdd();		//��� ��� ��ť���Ҫִ�еĲۺ���
	void ExecAddSql(int sno, QString cno, float f1,float f2,float f3);
	//�༶���н����������Ϣ��  Ҫִ�еĲۺ���
};

#endif // SCORE_TAB_H

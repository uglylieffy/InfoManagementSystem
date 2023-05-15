#pragma execution_character_set("utf-8")
#include "score_tab.h"

score_tab::score_tab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fresh_slot();
	connect(ui.fresh_pushButton, SIGNAL(clicked(bool)), this, SLOT(fresh_slot()));
	connect(ui.find_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnFind()));
	connect(ui.del_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnDel()));
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//����޸ģ������޸���Ϣ״̬
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//�ύ�޸�
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//�����޸�
	connect(ui.add_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));
}



score_tab::~score_tab()
{

}

void score_tab::fresh_slot() //��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳ���
{
	model = new QSqlQueryModel;
	model->setQuery(" select score.SNO as ѧ��,student.NAME as ����,CNAME as �γ�,Fscore as �����ɼ�,"
		"  Sscore as �����ɼ�,Lscore as ���޳ɼ� from score, course, student "
		" where score.SNO = student.SNO and course.CNO = score.CNO order by(score.SNO) ");       
	ui.tableView->setModel(model);

	//�����и�
	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
	{
		ui.tableView->setRowHeight(i, 20);
	}
}

void score_tab::onBtnFind()       //���Ҳۺ���
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("select course.CNO as �γ̺�,CNAME as �γ���,FScore as �����ɼ�,SScore as �����ɼ�,LScore as ���޳ɼ� "
		" from student, score, course where student.SNO = score.SNO AND "
		" score.CNO = course.CNO and student.SNO =%1 or student.NAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.tableView->setModel(model);
}

void score_tab::onBtnDel()	//ɾ���ۺ���
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("delete from score where SNO=%1 or NAME='%2'").arg(num).arg(name);


	QSqlQuery query;
	if (query.exec(sql))
	{
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ���ɹ�"));
		fresh_slot();    //ɾ���ɹ� ��ˢ��ҳ��
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ��ʧ��"));
}

void score_tab::onBtnMod() //����޸İ�ť�Ĳۺ���
{
	model2 = new QSqlTableModel(this);
	model2->setTable("score");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //��Ʊ༭����
	ui.tableView->setModel(model2);
}

void score_tab::onBtnSubmit()	//����ύ�޸ĵĲۺ���
{
	//��ʼ�������
	model2->database().transaction();
	if (model2->submitAll())
	{
		if (model2->database().commit())//�ύ
			QMessageBox::information(this, tr("tableModel"), tr("�����޸ĳɹ�!"));
	}
	else
	{
		model2->database().rollback(); //�ع�
		QMessageBox::warning(this, tr("tableModel"), tr("���ݿ����%1").arg(model->lastError().text()), QMessageBox::Ok);
	}
}

void score_tab::onBtnRollback()//��������޸ĵĲۺ���
{
	model2->revertAll();
}

void score_tab::onBtnAdd()    //��� ��� ��ť���Ҫִ�еĲۺ���
{
	m_pAddScore = new add_ScoreDlg();
	connect(m_pAddScore, SIGNAL(signaInfo(int, QString, float,float,float )), this, SLOT(ExecAddSql(int, QString, float,float ,float)));
	m_pAddScore->show();
}

void score_tab::ExecAddSql(int sno, QString cno, float f1,float f2,float f3)
{
	m_pAddScore->close();
	QString sql;
	sql = QString("insert into score ( SNO ,CNO,FScore,SScore,LScore) "
		" VALUES (%1, '%2' , %3,%4,%5)").arg(sno).arg(cno).arg(f1).arg(f2).arg(f3);
	QSqlQuery  query;

	bool ok = query.exec(sql);
	if (ok && num != 0)
	{
		QMessageBox::information(this, tr("��ʾ"), tr("��ӳɹ�!"));
		fresh_slot();    //����ɹ� ��ˢ��ҳ��
	}

	else
		QMessageBox::information(this, tr("��ʾ"), tr("���ʧ��!"));
}

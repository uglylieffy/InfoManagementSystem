#pragma execution_character_set("utf-8")
#include<qDebug>
#include "course_tab.h"

course_tab::course_tab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fresh_slot();
	connect(ui.fresh_pushButton, SIGNAL(clicked(bool)), this, SLOT(fresh_slot()));
	connect(ui.Find_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnFind()));
	connect(ui.Del_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnDel()));
	connect(ui.Add_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//����޸ģ������޸���Ϣ״̬
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//�ύ�޸�
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//�����޸�
}

course_tab::~course_tab()
{

}

void course_tab::fresh_slot() //��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳ���
{
	model = new QSqlQueryModel;
	model->setQuery("select * from Course");       //����ֱ������SQL��䣬�������һ������
	
	ui.tableView->setModel(model);
	

	//�����и�
	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
	{
		ui.tableView->setRowHeight(i, 20);
	}
}

void course_tab::onBtnFind()
{
	num = (ui.num_lineEdit->text()).toInt();
	qDebug() << "!!!!!!!!!!!!!!!!!!00" << ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString(" select Course.CNO as �γ̺�,Course.CNAME as �γ���, "
		" Course.TYPE �γ�����, COUNT(*) as ѡ������ from Course, Score "
		" where Course.CNO = Score.CNO and Course.CNO = %1 "
		" group by Course.CNO, Course.CNAME, Course.TYPE").arg(num);
	/*QString sql = QString("select CNO as �γ̺�,CNAME as �γ��� from Course "
						"where CNO=%1 or CNAME='%2'").arg(num).arg(name);*/
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.tableView->setModel(model);
}

void course_tab::onBtnDel()
{
	num = ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString("delete from course where CNO='%1' or CNAME='%2'").arg(num).arg(name);
	//QString sql2 = QString("delete from score where CNO='%1'or CNO=(select CNO from  stu where CNAME='%2')").arg(num).arg(name);


	//**********************ɾ����Ӧ��ѡ�γɼ�**********�����

	QSqlQuery query;
	if (query.exec(sql))//&&query.exec(sql2)
	{
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ���ɹ�"));
		fresh_slot();    //ɾ���ɹ� ��ˢ��ҳ��
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ��ʧ��"));
}

void course_tab::onBtnAdd()    //��� ��� ��ť���Ҫִ�еĲۺ���
{
	m_pAddCourseDlg = new addcoursedlg();
	connect(m_pAddCourseDlg, SIGNAL(signalInfo(QString, QString, QString, float, int, QString)), this, SLOT(ExecAddSql(QString, QString, QString, float, int, QString)));
	m_pAddCourseDlg->show();
}

void course_tab::onBtnMod() //����޸İ�ť�Ĳۺ���
{
	model2 = new QSqlTableModel(this);
	model2->setTable("course");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //��Ʊ༭����
	ui.tableView->setModel(model2);
}

void course_tab::onBtnSubmit()	//����ύ�޸ĵĲۺ���
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

void course_tab::onBtnRollback()//��������޸ĵĲۺ���
{
	model2->revertAll();
}


void course_tab::ExecAddSql(QString cno, QString tno, QString cname, float cre, int ctime, QString ctype)  //�����Ϣ������ϵ����OK������  
//signalStuInfo(int, QString, QString)�ź� ��Ӧ�Ĳۺ���
{
	m_pAddCourseDlg->close();
	QString sql;
	sql = QString("insert into Course ( CNO,TNO, CNAME ,CREDIT,CTIME,CTYPE) "
		" VALUES ('%1', '%2' , '%3',%4,%5,'%6')").arg(cno).arg(tno).arg(cname).arg(cre).arg(ctime).arg(ctype);
	QSqlQuery  query;

	bool ok = query.exec(sql);
	if (ok)
	{
		QMessageBox::information(this, tr("��ʾ"), tr("��ӳɹ�!"));
		fresh_slot();    //����ɹ� ��ˢ��ҳ��
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("���ʧ��!"));
}
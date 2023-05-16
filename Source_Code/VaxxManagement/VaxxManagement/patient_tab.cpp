#pragma execution_character_set("utf-8") //�ǳ���Ҫ��������ֱ������⣬��Ȼ���ֻ���ʾ������
#include "stu_tab.h"

stu_tab::stu_tab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	fresh_slot();
	connect(ui.stuFind_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnFind()));
	connect(ui.stuAdd_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));
	connect(ui.stuDel_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnDel()));
	connect(ui.stuFresh_pushButton, SIGNAL(clicked(bool)), this, SLOT(fresh_slot()));
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//����޸ģ������޸���Ϣ״̬
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//�ύ�޸�
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//�����޸�
	
}

stu_tab::~stu_tab()
{

}

void stu_tab::fresh_slot() //��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳ���
{
	model = new QSqlQueryModel;
	model->setQuery("select SNO as ѧ��, NAME as ����, SEX as �Ա�, AGE as ����, CLNAME as �༶" 
		" from student,class where student.CLNO=class.CLNO;");
												//����ֱ������SQL��䣬�������һ������
	ui.stu_tableView->setModel(model);

	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
		ui.stu_tableView->setRowHeight(i, 20);
}

void stu_tab::onBtnFind()
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("select * from student where SNO='%1' or NAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);    
	ui.stu_tableView->setModel(model);
}

void stu_tab::onBtnAdd()    //��� ��� ��ť���Ҫִ�еĲۺ���
{
	m_pAddStuDlg = new addStudlg();
	connect(m_pAddStuDlg, SIGNAL(signalStuInfo(int, QString, QString)), this, SLOT(ExecAddSql(int, QString, QString)));
	m_pAddStuDlg->show();
}

//signalStuInfo(int, QString, QString,int,QString)�ź� ��Ӧ�Ĳۺ���  �����Ϣ������ϵ����OK������ 
void stu_tab::ExecAddSql(int num, QString name, QString sex,int age,QString clno)  			
{
	m_pAddStuDlg->close();
	QString sql;
	sql = QString("insert into student ( SNO,SNAME ,SEX,AGE,CLNO)"
		" VALUES ('%1', '%2' , '%3',%4,'%5')").arg(num).arg(name).arg(sex).arg(age).arg(clno);
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

void stu_tab::onBtnDel()
{
	num = ui.num_lineEdit->text().toInt();
	//name = ui.name_lineEdit->text();
	QString sql = QString("delete from student where SNO=%1 or NAME='%2'").arg(num);
	QString sql2 = QString("delete from score where SNO='%1'").arg(num);

	QSqlQuery query;
	if (query.exec(sql)&&query.exec(sql2))
	{
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ���ɹ�"));
		fresh_slot();    //ɾ���ɹ� ��ˢ��ҳ��
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ��ʧ��"));
}


void stu_tab::onBtnMod() //����޸İ�ť�Ĳۺ���
{
	model2 = new QSqlTableModel(this);
	model2->setTable("score");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //��Ʊ༭����
	ui.stu_tableView->setModel(model2);
}

void stu_tab::onBtnSubmit()	//����ύ�޸ĵĲۺ���
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

void stu_tab::onBtnRollback()//��������޸ĵĲۺ���
{
	model2->revertAll();
}






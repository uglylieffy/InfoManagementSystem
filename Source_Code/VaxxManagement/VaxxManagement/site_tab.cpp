#include "class_tab.h"


class_tab::class_tab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fresh_slot();
	connect(ui.fresh_Button,SIGNAL(clicked(bool)),this,SLOT(fresh_slot()));
	connect(ui.find_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnFind()));
	connect(ui.del_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnDel()));
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//����޸ģ������޸���Ϣ״̬
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//�ύ�޸�
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//�����޸�
	connect(ui.add_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));//�����޸�
}

class_tab::~class_tab()
{

}

void class_tab::fresh_slot()
{
	model = new QSqlQueryModel;
	model->setQuery("select class.CLNO as �༶��,CLNAME as �༶����,ACNAME as ѧԺ"
		" from class, academy where class.ACNO = academy.ACNO");
	//����ֱ������SQL��䣬�������һ������
	ui.class_tableView->setModel(model);
	
	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
		ui.class_tableView->setRowHeight(i, 20);
}

void class_tab::onBtnFind()       //���Ҳۺ���
{
	num = ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString("select * from class where CLNO='%1' or CLNAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.class_tableView->setModel(model);
}

void class_tab::onBtnDel()	//ɾ���ۺ���
{
	num = ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString("delete from class where CLNO='%1' or CLNAME='%2'").arg(num).arg(name);
	//QString sql2 = QString("delete from student where SNO='%1'").arg(num);

		//******************ɾ����Ӧ�İ༶ѧ����ѧ���ɼ�********************�����


	QSqlQuery query;
	if (query.exec(sql))
	{
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ���ɹ�"));
		fresh_slot();    //ɾ���ɹ� ��ˢ��ҳ��
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ��ʧ��"));
}

void class_tab::onBtnMod() //����޸İ�ť�Ĳۺ���
{
	model2 = new QSqlTableModel(this);
	model2->setTable("class");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //��Ʊ༭����
	ui.class_tableView->setModel(model2);
}

void class_tab::onBtnSubmit()	//����ύ�޸ĵĲۺ���
{
	//��ʼ�������
	model2 -> database().transaction();
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

void class_tab::onBtnRollback()//��������޸ĵĲۺ���
{
	model2->revertAll();
}

void class_tab::onBtnAdd()    //��� ��� ��ť���Ҫִ�еĲۺ���
{
	m_pAddcla = new add_ClassDlg();
	connect(m_pAddcla, SIGNAL(signaInfo(QString, QString, int)), this, SLOT(ExecAddSql(QString, QString, int)));
	m_pAddcla->show();
}

void class_tab::ExecAddSql(QString nom, QString name, int acno)
{
	m_pAddcla->close();
	QString sql;
	sql = QString("insert into class ( CLNO ,CLNAME,ACNO) "
		" VALUES ('%1', '%2' , %3)").arg(nom).arg(name).arg(acno);
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

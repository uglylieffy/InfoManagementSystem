#include "teacher_tab.h"

teacher_tab::teacher_tab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fresh_slot();
	connect(ui.teaFind_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnFind()));
	connect(ui.teaAdd_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));
	connect(ui.teaDel_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnDel()));
	connect(ui.teaFresh_pushButton, SIGNAL(clicked(bool)), this, SLOT(fresh_slot()));
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//����޸ģ������޸���Ϣ״̬
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//�ύ�޸�
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//�����޸�
}

teacher_tab::~teacher_tab()
{

}

void teacher_tab::fresh_slot() //��� ˢ�� ��ť��ִ�в�ѯȫ��Ĳ���
{
	model = new QSqlQueryModel;
	model->setQuery("select TNO as ���, TNAME as ����, SEX as �Ա�, AGE as ����, POSITION as ְ������ "
		" from teacher;");
	//����ֱ������SQL��䣬�������һ������
	ui.tableView->setModel(model);

	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
		ui.tableView->setRowHeight(i, 20);
}

void teacher_tab::onBtnFind()
{
	num = ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString("select * from teacher where TNO='%1' or TNAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.tableView->setModel(model);
}

void teacher_tab::onBtnAdd()    //��� ��� ��ť���Ҫִ�еĲۺ���
{
	m_pAddTeacher = new add_TeacherDlg();
	connect(m_pAddTeacher, SIGNAL(signalStuInfo(int, QString, QString)), this, SLOT(ExecAddSql(int, QString, QString)));
	m_pAddTeacher->show();
}

//signalStuInfo(int, QString, QString,int,QString)�ź� ��Ӧ�Ĳۺ���  �����Ϣ������ϵ����OK������ 
void teacher_tab::ExecAddSql(int num, QString name, QString sex, int age, QString clno)
{
	m_pAddTeacher->close();
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

void teacher_tab::onBtnDel()
{
	num = ui.num_lineEdit->text().toInt();
	//name = ui.name_lineEdit->text();
	QString sql = QString("delete from teacher where TNO='%1'").arg(num);
	//QString sql2 = QString("delete from score where SNO='%1'").arg(num);

	QSqlQuery query;
	if (query.exec(sql))
	{
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ���ɹ�"));
		fresh_slot();    //ɾ���ɹ� ��ˢ��ҳ��
	}
	else
		QMessageBox::information(this, tr("��ʾ"), tr("ɾ��ʧ��"));
}


void teacher_tab::onBtnMod() //����޸İ�ť�Ĳۺ���
{
	model2 = new QSqlTableModel(this);
	model2->setTable("teacher");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //��Ʊ༭����
	ui.tableView->setModel(model2);
}

void teacher_tab::onBtnSubmit()	//����ύ�޸ĵĲۺ���
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

void teacher_tab::onBtnRollback()//��������޸ĵĲۺ���
{
	model2->revertAll();
}


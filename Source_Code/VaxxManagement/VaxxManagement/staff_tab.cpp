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
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//点击修改，进入修改信息状态
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//提交修改
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//撤销修改
}

teacher_tab::~teacher_tab()
{

}

void teacher_tab::fresh_slot() //点击 刷新 按钮后执行查询全表的操作
{
	model = new QSqlQueryModel;
	model->setQuery("select TNO as 编号, TNAME as 姓名, SEX as 性别, AGE as 年龄, POSITION as 职称名称 "
		" from teacher;");
	//这里直接设置SQL语句，忽略最后一个参数
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

void teacher_tab::onBtnAdd()    //点击 添加 按钮后的要执行的槽函数
{
	m_pAddTeacher = new add_TeacherDlg();
	connect(m_pAddTeacher, SIGNAL(signalStuInfo(int, QString, QString)), this, SLOT(ExecAddSql(int, QString, QString)));
	m_pAddTeacher->show();
}

//signalStuInfo(int, QString, QString,int,QString)信号 对应的槽函数  添加信息输入完毕点击“OK”键后 
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
		QMessageBox::information(this, tr("提示"), tr("添加成功!"));
		fresh_slot();    //插入成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("添加失败!"));
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
		QMessageBox::information(this, tr("提示"), tr("删除成功"));
		fresh_slot();    //删除成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("删除失败"));
}


void teacher_tab::onBtnMod() //点击修改按钮的槽函数
{
	model2 = new QSqlTableModel(this);
	model2->setTable("teacher");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //设计编辑策略
	ui.tableView->setModel(model2);
}

void teacher_tab::onBtnSubmit()	//点击提交修改的槽函数
{
	//开始事物操作
	model2->database().transaction();
	if (model2->submitAll())
	{
		if (model2->database().commit())//提交
			QMessageBox::information(this, tr("tableModel"), tr("数据修改成功!"));
	}
	else
	{
		model2->database().rollback(); //回滚
		QMessageBox::warning(this, tr("tableModel"), tr("数据库错误：%1").arg(model->lastError().text()), QMessageBox::Ok);
	}
}

void teacher_tab::onBtnRollback()//点击撤回修改的槽函数
{
	model2->revertAll();
}


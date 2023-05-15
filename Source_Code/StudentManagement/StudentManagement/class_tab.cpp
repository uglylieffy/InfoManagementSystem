#include "class_tab.h"


class_tab::class_tab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	fresh_slot();
	connect(ui.fresh_Button,SIGNAL(clicked(bool)),this,SLOT(fresh_slot()));
	connect(ui.find_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnFind()));
	connect(ui.del_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnDel()));
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//点击修改，进入修改信息状态
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//提交修改
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//撤销修改
	connect(ui.add_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));//撤销修改
}

class_tab::~class_tab()
{

}

void class_tab::fresh_slot()
{
	model = new QSqlQueryModel;
	model->setQuery("select class.CLNO as 班级号,CLNAME as 班级名称,ACNAME as 学院"
		" from class, academy where class.ACNO = academy.ACNO");
	//这里直接设置SQL语句，忽略最后一个参数
	ui.class_tableView->setModel(model);
	
	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
		ui.class_tableView->setRowHeight(i, 20);
}

void class_tab::onBtnFind()       //查找槽函数
{
	num = ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString("select * from class where CLNO='%1' or CLNAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.class_tableView->setModel(model);
}

void class_tab::onBtnDel()	//删除槽函数
{
	num = ui.num_lineEdit->text();
	name = ui.name_lineEdit->text();
	QString sql = QString("delete from class where CLNO='%1' or CLNAME='%2'").arg(num).arg(name);
	//QString sql2 = QString("delete from student where SNO='%1'").arg(num);

		//******************删除相应的班级学生和学生成绩********************待解决


	QSqlQuery query;
	if (query.exec(sql))
	{
		QMessageBox::information(this, tr("提示"), tr("删除成功"));
		fresh_slot();    //删除成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("删除失败"));
}

void class_tab::onBtnMod() //点击修改按钮的槽函数
{
	model2 = new QSqlTableModel(this);
	model2->setTable("class");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //设计编辑策略
	ui.class_tableView->setModel(model2);
}

void class_tab::onBtnSubmit()	//点击提交修改的槽函数
{
	//开始事物操作
	model2 -> database().transaction();
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

void class_tab::onBtnRollback()//点击撤回修改的槽函数
{
	model2->revertAll();
}

void class_tab::onBtnAdd()    //点击 添加 按钮后的要执行的槽函数
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
		QMessageBox::information(this, tr("提示"), tr("添加成功!"));
		fresh_slot();    //插入成功 就刷新页面
	}

	else
		QMessageBox::information(this, tr("提示"), tr("添加失败!"));
}

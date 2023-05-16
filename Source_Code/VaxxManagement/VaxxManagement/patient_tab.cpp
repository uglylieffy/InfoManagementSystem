#pragma execution_character_set("utf-8") //非常重要，解决汉字编码问题，不然汉字会显示不正常
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
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//点击修改，进入修改信息状态
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//提交修改
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//撤销修改
	
}

stu_tab::~stu_tab()
{

}

void stu_tab::fresh_slot() //点击 刷新 按钮后执行查询全表的操作
{
	model = new QSqlQueryModel;
	model->setQuery("select SNO as 学号, NAME as 姓名, SEX as 性别, AGE as 年龄, CLNAME as 班级" 
		" from student,class where student.CLNO=class.CLNO;");
												//这里直接设置SQL语句，忽略最后一个参数
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

void stu_tab::onBtnAdd()    //点击 添加 按钮后的要执行的槽函数
{
	m_pAddStuDlg = new addStudlg();
	connect(m_pAddStuDlg, SIGNAL(signalStuInfo(int, QString, QString)), this, SLOT(ExecAddSql(int, QString, QString)));
	m_pAddStuDlg->show();
}

//signalStuInfo(int, QString, QString,int,QString)信号 对应的槽函数  添加信息输入完毕点击“OK”键后 
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
		QMessageBox::information(this, tr("提示"), tr("添加成功!"));
		fresh_slot();    //插入成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("添加失败!"));
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
		QMessageBox::information(this, tr("提示"), tr("删除成功"));
		fresh_slot();    //删除成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("删除失败"));
}


void stu_tab::onBtnMod() //点击修改按钮的槽函数
{
	model2 = new QSqlTableModel(this);
	model2->setTable("score");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //设计编辑策略
	ui.stu_tableView->setModel(model2);
}

void stu_tab::onBtnSubmit()	//点击提交修改的槽函数
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

void stu_tab::onBtnRollback()//点击撤回修改的槽函数
{
	model2->revertAll();
}






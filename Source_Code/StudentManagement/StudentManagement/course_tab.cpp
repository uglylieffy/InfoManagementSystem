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
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//点击修改，进入修改信息状态
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//提交修改
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//撤销修改
}

course_tab::~course_tab()
{

}

void course_tab::fresh_slot() //点击 刷新 按钮后执行查询全表的操作
{
	model = new QSqlQueryModel;
	model->setQuery("select * from Course");       //这里直接设置SQL语句，忽略最后一个参数
	
	ui.tableView->setModel(model);
	

	//设置行高
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
	QString sql = QString(" select Course.CNO as 课程号,Course.CNAME as 课程名, "
		" Course.TYPE 课程类型, COUNT(*) as 选课人数 from Course, Score "
		" where Course.CNO = Score.CNO and Course.CNO = %1 "
		" group by Course.CNO, Course.CNAME, Course.TYPE").arg(num);
	/*QString sql = QString("select CNO as 课程号,CNAME as 课程名 from Course "
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


	//**********************删除相应的选课成绩**********待解决

	QSqlQuery query;
	if (query.exec(sql))//&&query.exec(sql2)
	{
		QMessageBox::information(this, tr("提示"), tr("删除成功"));
		fresh_slot();    //删除成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("删除失败"));
}

void course_tab::onBtnAdd()    //点击 添加 按钮后的要执行的槽函数
{
	m_pAddCourseDlg = new addcoursedlg();
	connect(m_pAddCourseDlg, SIGNAL(signalInfo(QString, QString, QString, float, int, QString)), this, SLOT(ExecAddSql(QString, QString, QString, float, int, QString)));
	m_pAddCourseDlg->show();
}

void course_tab::onBtnMod() //点击修改按钮的槽函数
{
	model2 = new QSqlTableModel(this);
	model2->setTable("course");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //设计编辑策略
	ui.tableView->setModel(model2);
}

void course_tab::onBtnSubmit()	//点击提交修改的槽函数
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

void course_tab::onBtnRollback()//点击撤回修改的槽函数
{
	model2->revertAll();
}


void course_tab::ExecAddSql(QString cno, QString tno, QString cname, float cre, int ctime, QString ctype)  //添加信息输入完毕点击“OK”键后  
//signalStuInfo(int, QString, QString)信号 对应的槽函数
{
	m_pAddCourseDlg->close();
	QString sql;
	sql = QString("insert into Course ( CNO,TNO, CNAME ,CREDIT,CTIME,CTYPE) "
		" VALUES ('%1', '%2' , '%3',%4,%5,'%6')").arg(cno).arg(tno).arg(cname).arg(cre).arg(ctime).arg(ctype);
	QSqlQuery  query;

	bool ok = query.exec(sql);
	if (ok)
	{
		QMessageBox::information(this, tr("提示"), tr("添加成功!"));
		fresh_slot();    //插入成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("添加失败!"));
}
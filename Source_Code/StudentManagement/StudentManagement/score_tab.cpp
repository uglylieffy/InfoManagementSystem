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
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//点击修改，进入修改信息状态
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//提交修改
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//撤销修改
	connect(ui.add_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));
}



score_tab::~score_tab()
{

}

void score_tab::fresh_slot() //点击 刷新 按钮后执行查询全表的操作
{
	model = new QSqlQueryModel;
	model->setQuery(" select score.SNO as 学号,student.NAME as 姓名,CNAME as 课程,Fscore as 正考成绩,"
		"  Sscore as 补考成绩,Lscore as 重修成绩 from score, course, student "
		" where score.SNO = student.SNO and course.CNO = score.CNO order by(score.SNO) ");       
	ui.tableView->setModel(model);

	//设置行高
	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
	{
		ui.tableView->setRowHeight(i, 20);
	}
}

void score_tab::onBtnFind()       //查找槽函数
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("select course.CNO as 课程号,CNAME as 课程名,FScore as 正考成绩,SScore as 补考成绩,LScore as 重修成绩 "
		" from student, score, course where student.SNO = score.SNO AND "
		" score.CNO = course.CNO and student.SNO =%1 or student.NAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.tableView->setModel(model);
}

void score_tab::onBtnDel()	//删除槽函数
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("delete from score where SNO=%1 or NAME='%2'").arg(num).arg(name);


	QSqlQuery query;
	if (query.exec(sql))
	{
		QMessageBox::information(this, tr("提示"), tr("删除成功"));
		fresh_slot();    //删除成功 就刷新页面
	}
	else
		QMessageBox::information(this, tr("提示"), tr("删除失败"));
}

void score_tab::onBtnMod() //点击修改按钮的槽函数
{
	model2 = new QSqlTableModel(this);
	model2->setTable("score");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //设计编辑策略
	ui.tableView->setModel(model2);
}

void score_tab::onBtnSubmit()	//点击提交修改的槽函数
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

void score_tab::onBtnRollback()//点击撤回修改的槽函数
{
	model2->revertAll();
}

void score_tab::onBtnAdd()    //点击 添加 按钮后的要执行的槽函数
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
		QMessageBox::information(this, tr("提示"), tr("添加成功!"));
		fresh_slot();    //插入成功 就刷新页面
	}

	else
		QMessageBox::information(this, tr("提示"), tr("添加失败!"));
}

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
	connect(ui.modify_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnMod()));//???????????????????
	connect(ui.submit_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnSubmit()));//?????
	connect(ui.rollback_Button, SIGNAL(clicked(bool)), this, SLOT(onBtnRollback()));//???????
	connect(ui.add_pushButton, SIGNAL(clicked(bool)), this, SLOT(onBtnAdd()));
}



score_tab::~score_tab()
{

}

void score_tab::fresh_slot() //??? ??? ???????????????????
{
	model = new QSqlQueryModel;
	model->setQuery(" select score.SNO as ???,student.NAME as ????,CNAME as ????,Fscore as ???????,"
		"  Sscore as ???????,Lscore as ?????? from score, course, student "
		" where score.SNO = student.SNO and course.CNO = score.CNO order by(score.SNO) ");       
	ui.tableView->setModel(model);

	//????????
	int row_count = model->rowCount();
	for (int i = 0; i < row_count; i++)
	{
		ui.tableView->setRowHeight(i, 20);
	}
}

void score_tab::onBtnFind()       //????????
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("select course.CNO as ?????,CNAME as ??????,FScore as ???????,SScore as ???????,LScore as ?????? "
		" from student, score, course where student.SNO = score.SNO AND "
		" score.CNO = course.CNO and student.SNO =%1 or student.NAME='%2'").arg(num).arg(name);
	model = new QSqlQueryModel;
	model->setQuery(sql);
	ui.tableView->setModel(model);
}

void score_tab::onBtnDel()	//????????
{
	num = ui.num_lineEdit->text().toInt();
	name = ui.name_lineEdit->text();
	QString sql = QString("delete from score where SNO=%1 or NAME='%2'").arg(num).arg(name);


	QSqlQuery query;
	if (query.exec(sql))
	{
		QMessageBox::information(this, tr("???"), tr("??????"));
		fresh_slot();    //?????? ????????
	}
	else
		QMessageBox::information(this, tr("???"), tr("??????"));
}

void score_tab::onBtnMod() //??????????????
{
	model2 = new QSqlTableModel(this);
	model2->setTable("score");
	model2->select();
	model2->setEditStrategy(QSqlTableModel::OnManualSubmit); //????????
	ui.tableView->setModel(model2);
}

void score_tab::onBtnSubmit()	//?????????????
{
	//??????????
	model2->database().transaction();
	if (model2->submitAll())
	{
		if (model2->database().commit())//??
			QMessageBox::information(this, tr("tableModel"), tr("?????????!"));
	}
	else
	{
		model2->database().rollback(); //???
		QMessageBox::warning(this, tr("tableModel"), tr("????????%1").arg(model->lastError().text()), QMessageBox::Ok);
	}
}

void score_tab::onBtnRollback()//???????????????
{
	model2->revertAll();
}

void score_tab::onBtnAdd()    //??? ???? ????????????????
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
		QMessageBox::information(this, tr("???"), tr("??????!"));
		fresh_slot();    //?????? ????????
	}

	else
		QMessageBox::information(this, tr("???"), tr("???????!"));
}

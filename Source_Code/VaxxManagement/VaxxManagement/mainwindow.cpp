#pragma execution_character_set("utf-8")

#include "mainwindow.h"
mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pStuTab = new stu_tab();
	m_pCourseTab = new course_tab();
	m_pScoreTab = new score_tab();
	m_pClassTab = new class_tab();
	m_pTeacherTab = new teacher_tab();

	ui.tabWidget->addTab(m_pStuTab,tr("??????"));
	ui.tabWidget->addTab(m_pCourseTab, tr("?¦Ã????"));
	ui.tabWidget->addTab(m_pScoreTab, tr("??????"));
	ui.tabWidget->addTab(m_pClassTab, tr("?????"));
	ui.tabWidget->addTab(m_pTeacherTab, tr("??????"));
}

mainwindow::~mainwindow()
{

}

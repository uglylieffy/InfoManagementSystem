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

	ui.tabWidget->addTab(m_pStuTab,tr("学生信息"));
	ui.tabWidget->addTab(m_pCourseTab, tr("课程信息"));
	ui.tabWidget->addTab(m_pScoreTab, tr("选课情况"));
	ui.tabWidget->addTab(m_pClassTab, tr("班级信息"));
	ui.tabWidget->addTab(m_pTeacherTab, tr("教师信息"));
}

mainwindow::~mainwindow()
{

}

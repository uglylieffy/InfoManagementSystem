#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include"stu_tab.h"
#include"course_tab.h"
#include"score_tab.h"
#include"class_tab.h"
#include"qtabwidget.h"
#include"teacher_tab.h"

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();

private:
	Ui::mainwindowClass ui;
	stu_tab * m_pStuTab;
	course_tab * m_pCourseTab;
	score_tab * m_pScoreTab;
	class_tab * m_pClassTab;
	teacher_tab *m_pTeacherTab;
};

#endif // MAINWINDOW_H

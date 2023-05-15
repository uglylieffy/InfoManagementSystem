#ifndef ADDSTUDLG_H
#define ADDSTUDLG_H

#include <QDialog>


namespace Ui {
class addStudlg;
}

class addStudlg : public QDialog
{
	Q_OBJECT;

public:
    explicit addStudlg(QWidget *parent = 0);
    ~addStudlg();

private slots:
    void ok_button();

signals:
    void signalStuInfo(int,QString,QString,int,QString);



private:
    Ui::addStudlg *ui;
};

#endif // ADDSTUDLG_H

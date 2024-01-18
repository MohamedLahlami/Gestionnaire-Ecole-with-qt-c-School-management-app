#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "controlpanel.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_toRegisterPage_btn_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    ControlPanel *controlpanel;
};
#endif // MAINWINDOW_H

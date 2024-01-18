#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap icon("D:/EMSI/cpp/CPP Project/projectCPP/EMSI.png");
    ui->icon->setPixmap(icon);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gestemptemp.db");
    if(db.open())
    {
        qDebug() << "database is connected";
    }
    else
    {
        qDebug() << "database is not connected";
        qDebug() << "error: " << db.lastError();
    }
    ControlPanel::execQuery("CREATE TABLE IF NOT EXISTS admins(id INTEGER PRIMARY KEY, username VARCHAR NOT NULL, password VARCHAR NOT NULL)");
    ControlPanel::execQuery("INSERT INTO admins VALUES (1, 'admin', 'admin') ON CONFLICT DO NOTHING");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    db.open();
    QSqlDatabase::database().transaction();
    QSqlQuery query(db);
    query.exec("SELECT * FROM admins WHERE username='"+username+"' AND password='"+password+"'");
    QSqlDatabase::database().commit();
    if(query.next())
    {
        controlpanel = new ControlPanel(this);
        controlpanel->show();
    }
    db.close();
}

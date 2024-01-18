#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QtSql>
#include "execQuery.cpp"
#include <QMessageBox>


namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

    static bool execQuery(QString query){
        QSqlDatabase::database().transaction();
        QSqlQuery Q;
        Q.prepare(query);
        if(Q.exec())
        {
            qDebug() << "Query is executed successfully";
            QSqlDatabase::database().commit();
            return true;
        }
        else
        {
            qDebug() << "Query execution NOT successful";
            qDebug() << query;
            qDebug() << "Error: " << QSqlDatabase::database().lastError().text();
            QSqlDatabase::database().commit();
            return false;
        }

    }

private slots:
    void on_studentAdd_clicked();

    void on_studentEdit_clicked();

    void on_studentDelete_clicked();

    void on_studentShow_clicked();

    void on_ProfAdd_clicked();

    void on_profEdit_clicked();

    void on_profDelete_clicked();

    void on_profShow_clicked();

    void on_SubjectAdd_clicked();

    void on_subjectEdit_clicked();

    void on_subjectDelete_clicked();

    void on_subjectShow_clicked();

    void on_groupAdd_clicked();

    void on_groupEdit_clicked();

    void on_groupDelete_clicked();

    void on_groupShow_clicked();

private:
    Ui::ControlPanel *ui;
    QSqlDatabase db;
};

#endif // CONTROLPANEL_H

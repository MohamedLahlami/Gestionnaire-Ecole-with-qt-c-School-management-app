#include "controlpanel.h"
#include "ui_controlpanel.h"
ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
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
    execQuery("CREATE TABLE IF NOT EXISTS subjects(id INTEGER PRIMARY KEY, label VARCHAR, code INT, coef INT)");
    execQuery("CREATE TABLE IF NOT EXISTS groups(id INTEGER PRIMARY KEY, code INT, year INT)");
    execQuery("CREATE TABLE IF NOT EXISTS students(id INTEGER PRIMARY KEY, lname VARCHAR, fname VARCHAR, age INT, studentGroup INT, CNE INT, CIN INT NOT NULL, FOREIGN KEY(studentGroup) REFERENCES groups(id))");
    execQuery("CREATE TABLE IF NOT EXISTS teachers(id INTEGER PRIMARY KEY, lname VARCHAR, fname VARCHAR, code INT NOT NULL, subject INT, FOREIGN KEY(subject) REFERENCES subjects(id))");
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

//AJOUTER ETUDIANT
void ControlPanel::on_studentAdd_clicked()
{
    QString lname = ui->studentLName->text();
    QString fname = ui->studentFName->text();
    QString age = ui->studentAge->text();
    QString group = ui->studentGroup->text();
    QString CNE = ui->studentCNE->text();
    QString CIN = ui->studentCIN->text();
    QString query = "INSERT INTO students(lname, fname, age, studentGroup, CNE, CIN) VALUES ('"+lname+"', '"+fname+"', "+age+", "+group+", "+CNE+", "+CIN+")";
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "L'etudiant a été ajouté avec succèss");
    }
}

//EDITER ETUDIANT
void ControlPanel::on_studentEdit_clicked()
{
    QString lname = ui->studentLName->text();
    QString fname = ui->studentFName->text();
    QString age = ui->studentAge->text();
    QString group = ui->studentGroup->text();
    QString CNE = ui->studentCNE->text();
    QString CIN = ui->studentCIN->text();
    QString query = "UPDATE TABLE students SET lname = '"+lname+"', fname = '"+fname+"', age = "+age+",studentGroup = "+group+", CNE = "+CNE+" WHERE CIN = " + CIN;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "L'etudiant a été modifié avec succèss");
    }
}

//SUPPRIMER ETUDIANT
void ControlPanel::on_studentDelete_clicked()
{
    QString CIN = ui->studentCIN->text();
    QString query = "DELETE FROM students WHERE CIN = "+CIN;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "L'etudiant a été supprimé avec succèss");
    }
}

//AFFICHER ETUDIANT
void ControlPanel::on_studentShow_clicked()
{
    QString query = "SELECT * FROM students";
    QSqlQueryModel *model;
    model = new QSqlQueryModel(this);
    model->setQuery(query);
    ui->tableView->setModel(model);
}

//AJOUTER PROF
void ControlPanel::on_ProfAdd_clicked()
{
    QString lname = ui->profLName->text();
    QString fname = ui->profFName->text();
    QString code = ui->profCode->text();
    QString subject = ui->profSubject->text();
    QString query = "INSERT INTO teachers(lname, fname, code, subject) VALUES('"+lname+"', '"+fname+"', "+code+", "+subject+")";
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "Le professeur a été ajouté avec succèss");
    }
}

//EDITER PROF
void ControlPanel::on_profEdit_clicked()
{
    QString lname = ui->profLName->text();
    QString fname = ui->profLName->text();
    QString code = ui->profCode->text();
    QString subject = ui->profSubject->text();
    QString query = "UPDATE TABLE teachers SET lname = '"+lname+"', fname = '"+fname+"', subject ="+subject+" WHERE code ="+code;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "Le professeur a été modifié avec succèss");
    }
}

//SUPPRIMER PROF
void ControlPanel::on_profDelete_clicked()
{
    QString code = ui->profCode->text();
    QString query = "DELETE FROM teachers WHERE code = "+code;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "Le professeur a été supprimé avec succèss");
    }
}

//AFFICHER PROF
void ControlPanel::on_profShow_clicked()
{
    QString query = "SELECT * FROM teachers";
    QSqlQueryModel *model;
    model = new QSqlQueryModel(this);
    model->setQuery(query);
    ui->tableView->setModel(model);
}

//AJOUTER MATIERE
void ControlPanel::on_SubjectAdd_clicked()
{
    QString label = ui->subjectLabel->text();
    QString code = ui->subjectCode->text();
    QString coef = ui->subjectCoef->text();
    QString query = "INSERT INTO subjects(label, code, coef) VALUES ('"+label+"', "+code+", "+coef+")";
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "La matière a été ajoutée avec succèss");
    }
}

//EDITER MATIERE
void ControlPanel::on_subjectEdit_clicked()
{
    QString label = ui->subjectLabel->text();
    QString code = ui->subjectCode->text();
    QString coef = ui->subjectCoef->text();
    QString query = "UPDATE TABLE subjects set label = '"+label+"', coef ="+coef+" WHERE code = "+code;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "La matière a été modifiée avec succèss");
    }
}

//SUPPRIMER MATIERE
void ControlPanel::on_subjectDelete_clicked()
{
    QString code = ui->subjectCode->text();
    QString query = "DELETE FROM subjects WHERE code ="+code;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "La matière a été supprimée avec succèss");
    }
}

//AFFICHER MATIERE
void ControlPanel::on_subjectShow_clicked()
{
    QString query = "SELECT * FROM subjects";
    QSqlQueryModel *model;
    model = new QSqlQueryModel(this);
    model->setQuery(query);
    ui->tableView->setModel(model);
}

//AJOUTER GROUPE
void ControlPanel::on_groupAdd_clicked()
{
    QString code = ui->groupNumber->text();
    QString year = ui->groupYear->text();
    QString query = "INSERT INTO groups(code, year) VALUES( "+code+", "+year+")";
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "Le group a été ajouté avec succèss");
    }
}

//EDITER GROUPE
void ControlPanel::on_groupEdit_clicked()
{
    QString code = ui->groupNumber->text();
    QString year = ui->groupYear->text();
    QString query = "UPDATE TABLE groups SET year ="+year+" WHERE code = "+code;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "Le group a été modifié avec succèss");
    }
}

//SUPPRIMER GROUPE
void ControlPanel::on_groupDelete_clicked()
{
    QString code = ui->groupNumber->text();
    QString query = "DELETE FROM groups WHERE code="+code;
    if(execQuery(query))
    {
        QMessageBox::information(this, "Query status", "Le group a été supprimé avec succèss");
    }
}

//AFFICHER GROUPE
void ControlPanel::on_groupShow_clicked()
{
    QString query = "SELECT * FROM groups";
    QSqlQueryModel *model;
    model = new QSqlQueryModel(this);
    model->setQuery(query);
    ui->tableView->setModel(model);
}


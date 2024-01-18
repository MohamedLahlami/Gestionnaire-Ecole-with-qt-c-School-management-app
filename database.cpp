#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

int main(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");

    // Check if the connection is successful
    if (!db.open()) {
        qDebug() << "Failed to connect to the database:";
        return 1;
    }

    // Create the database if it doesn't exist
    QSqlQuery createDatabaseQuery;
    if (!createDatabaseQuery.exec("CREATE DATABASE IF NOT EXISTS gestemptemps")) {
        qDebug() << "Failed to create database:";
        return 1;
    }

    // Use the created database
    db.setDatabaseName("gestemptemps");
    if (!db.open()) {
        qDebug() << "Failed to open the database:";
        return 1;
    }

    // Create the 'users' table if it doesn't exist
    QSqlQuery createTableQuery;
    if (!createTableQuery.exec("CREATE TABLE IF NOT EXISTS users (id INT PRIMARY KEY, name VARCHAR(50))")) {
        qDebug() << "Failed to create table:";
        return 1;
    }

    qDebug() << "Database and table created successfully.";
}

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/zhihongzeng/zhzeng/coding/db.sqlite");

//    MainWindow w;
//    w.show();
    
    return a.exec();
}

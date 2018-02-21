#include "mmainwindow.h"
#include "mentrydialog.h"
#include <QApplication>
#include <QtSql>
/* Функцция тестового подкючения
bool dbConnect () {

    static QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("PascalHate1");

    if (db.open())
        qDebug() << "\nDb opened!";
    else
        return 0;
    qDebug() << db.driver();

    if (db.tables().count() != 0) {
        QSqlQuery query ("DROP TABLE persons");
        qDebug() << "\nOld table droped!";
    }

    QSqlQuery query ("CREATE TABLE persons ("
                    "key integer PRIMARY KEY,"
                    "secondname varchar(255)"
                    ")");

    qDebug() << query.lastError().text();

    query.prepare("INSERT INTO Persons (key, secondname)"
                  "VALUES (:key, :secondname);");

    for (int i = 0; i < 10; ++i) {
        query.bindValue(":key", QString::number(i));
        query.bindValue(":secondname", QString("SecondName") + QString::number(i));
        if (!query.exec())
            qDebug() << query.lastError().text();
            qDebug() << query.executedQuery();
    }

    qDebug() << "\nNew table created.";
    qDebug() << db.drivers();

    return 1;
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //dbConnect();

    //mEntryDialog * c = new mEntryDialog();
    //c->show();
    mMainWindow w;
    //QObject::connect(c, mEntryDialog::dbConnected,
    //                 &w, mMainWindow::show);
    w.show();
    return a.exec();
}

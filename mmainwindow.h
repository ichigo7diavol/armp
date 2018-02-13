#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include <QDebug>
#include <QMdiSubWindow>
#include <QtSql>
#include <QTableView>
#include <random>
#include <ctime>
#include <QMessageBox>

namespace Ui {
class mMainWindow;
}

class mMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mMainWindow(QWidget *parent = 0);
    ~mMainWindow();

private:
    Ui::mMainWindow *ui;

    QSqlTableModel * pastm; // ptr to ab sql table model
    QTableView * patv;      // ptr to ab table view
    QMainWindow * pasw;     //ptr to abiturient sub window

public slots:
    void openAbiturientsTable () {};
    void randomSecondName ();
};

#endif // MMAINWINDOW_H

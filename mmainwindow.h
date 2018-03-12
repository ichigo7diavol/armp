#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include <QDebug>
#include <QMdiSubWindow>
#include <QtSql>
#include <QMessageBox>
#include <QStringList>

#include "mabiturtablewindow.h"
#include "othertableswindow.h"

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
    Ui::mMainWindow * ui;

public slots:
    void openAbiturientsTable ();
    void openDisciplineTable();
};

#endif // MMAINWINDOW_H

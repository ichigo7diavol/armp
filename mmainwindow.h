#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include <QDebug>
#include <QMdiSubWindow>
#include <QtSql>
#include <QMessageBox>
#include <QStringList>

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

public slots:
    void openAbiturientsTable () {}
};

#endif // MMAINWINDOW_H

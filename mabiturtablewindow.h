#ifndef MABITURTABLEWINDOW_H
#define MABITURTABLEWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "precompileconstants.h"
#include "maddabiturdialog.h"

namespace Ui {
class mAbiturTableWindow;
}

class mAbiturTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mAbiturTableWindow(QWidget *parent = 0);
    ~mAbiturTableWindow();

public slots:
    void addRow();

private:
    Ui::mAbiturTableWindow *ui;
    QSqlRelationalTableModel * ptm;

};

#endif // MABITURTABLEWINDOW_H

#ifndef MABITURTABLEWINDOW_H
#define MABITURTABLEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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
    void addRowButton();
    void addRow(QList <QVariant> &);

private:
    Ui::mAbiturTableWindow *ui; // ui
    QSqlRelationalTableModel * ptm; // ptr to main table model
    QVector <QString*> av; // atribute vector

    char bri;
};

#endif // MABITURTABLEWINDOW_H

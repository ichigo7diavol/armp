#ifndef MADDABITURDIALOG_H
#define MADDABITURDIALOG_H

#include <QDialog>
#include <QtSql>
#include <precompileconstants.h>

namespace Ui {
class mAddAbiturDialog;
}

class mAddAbiturDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddAbiturDialog(QWidget *parent = 0);
    ~mAddAbiturDialog();

public slots:
    void formCortege();

signals:
    void cortegeFormed (QSqlRecord &);

private:
    Ui::mAddAbiturDialog *ui;

    QSqlTableModel * pelcbm; // ptr to education lvl combo box model
    QSqlTableModel * pbcbm; //ptr to benefit combo box model
    QSqlRecord * par; // ptr to abit record
};

#endif // MADDABITURDIALOG_H

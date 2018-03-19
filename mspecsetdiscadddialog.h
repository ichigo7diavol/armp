#ifndef MSPECSETDISCADDDIALOG_H
#define MSPECSETDISCADDDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mSpecSetDiscAddDialog;
}

class mSpecSetDiscAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mSpecSetDiscAddDialog(QWidget *parent = 0);
    ~mSpecSetDiscAddDialog();

signals:
    void cortegeFormed(QList<QVariant>&);

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);


private:
    Ui::mSpecSetDiscAddDialog *ui;

    QSqlTableModel * ptm;
};

#endif // MSPECSETDISCADDDIALOG_H

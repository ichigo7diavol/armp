#ifndef MADDBENIFITDIALOG_H
#define MADDBENIFITDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mAddBenifitDialog;
}

class mAddBenifitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddBenifitDialog(QWidget *parent = 0);
    ~mAddBenifitDialog();

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord & rec);

signals:
    void cortegeFormed(QList<QVariant> &);

private:
    Ui::mAddBenifitDialog *ui;
};

#endif // MADDBENIFITDIALOG_H

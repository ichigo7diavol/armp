#ifndef MESTABLISHMENTEDITDIALOG_H
#define MESTABLISHMENTEDITDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mEstablishmentEditDialog;
}

class mEstablishmentEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mEstablishmentEditDialog(QWidget *parent = 0);
    ~mEstablishmentEditDialog();

private:
    Ui::mEstablishmentEditDialog *ui;

    QSqlTableModel * etm;
};

#endif // MESTABLISHMENTEDITDIALOG_H

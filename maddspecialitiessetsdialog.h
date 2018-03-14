#ifndef MADDSPECIALITIESSETSDIALOG_H
#define MADDSPECIALITIESSETSDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mAddSpecialitiesSetsDialog;
}

class mAddSpecialitiesSetsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddSpecialitiesSetsDialog(QWidget *parent = 0);
    ~mAddSpecialitiesSetsDialog();

private:
    Ui::mAddSpecialitiesSetsDialog *ui;

    QSqlTableModel * ptm;
    QSqlTableModel * pptm;
};

#endif // MADDSPECIALITIESSETSDIALOG_H

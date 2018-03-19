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

signals:
    void cortegeFormed(QList<QVariant>&);

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);

private:
    Ui::mAddSpecialitiesSetsDialog *ui;

    QSqlTableModel * pstm;
    QSqlTableModel * ppstm;

    QSqlTableModel * petm;
    QSqlTableModel * ppetm;

    QSqlTableModel * pftm;
    QSqlTableModel * ppftm;
};

#endif // MADDSPECIALITIESSETSDIALOG_H

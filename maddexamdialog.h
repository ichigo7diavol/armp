#ifndef MADDEXAMDIALOG_H
#define MADDEXAMDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mAddExamDialog;
}

class mAddExamDialog : public QDialog
{
    Q_OBJECT

signals:
    void cortegeFormed(QList <QVariant> &);

public:
    explicit mAddExamDialog(QWidget *parent = 0);
    ~mAddExamDialog();

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);

private:
    Ui::mAddExamDialog *ui;

    QSqlTableModel * ttm; // type table model
    QSqlTableModel * dtm; // discipline table model
};

#endif // MADDEXAMDIALOG_H

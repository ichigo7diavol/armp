#ifndef ADDABITURDOCSDIALOG_H
#define ADDABITURDOCSDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mAddAbiturDocsDialog;
}

class mAddAbiturDocsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddAbiturDocsDialog(QWidget *parent = 0);
    ~mAddAbiturDocsDialog();

public slots:
    void fillCortege(const QSqlRecord &);
    void formCortege();

signals:
    void cortegeFormed(QList<QVariant> &);

private:
    Ui::mAddAbiturDocsDialog *ui;

    QSqlTableModel * ntm; // document types dialog
};

#endif // ADDABITURDOCSDIALOG_H

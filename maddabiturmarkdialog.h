#ifndef MADDABITURMARKDIALOG_H
#define MADDABITURMARKDIALOG_H

#include <QDialog>
#include <QtSql>

#include "precompileconstants.h"

namespace Ui {
class mAddAbiturMarkDialog;
}

class mAddAbiturMarkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddAbiturMarkDialog(QWidget *parent = 0);
    ~mAddAbiturMarkDialog();

public slots:
    void fillCortege(const QSqlRecord &);
    void formCortege();

signals:
    void cortegeFormed(QList<QVariant> &);

private:
    Ui::mAddAbiturMarkDialog *ui;

    QSqlTableModel * ptm;
};

#endif // MADDABITURMARKDIALOG_H

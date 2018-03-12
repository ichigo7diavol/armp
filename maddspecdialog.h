#ifndef MADDSPECDIALOG_H
#define MADDSPECDIALOG_H

#include <QDialog>
#include <QtSql>

#include <precompileconstants.h>

namespace Ui {
class mAddSpecDialog;
}

class mAddSpecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddSpecDialog(QWidget *parent = 0);
    ~mAddSpecDialog();

signals:
    void cortegeFormed(QList<QVariant>&);

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);

private:
    Ui::mAddSpecDialog *ui;

    QSqlTableModel * pstm; // specs
    QSqlTableModel * pftm; // finance
    QSqlTableModel * petm; // educ

};

#endif // MADDSPECDIALOG_H

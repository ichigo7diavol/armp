#ifndef MADDDISCIPLINEDIALOG_H
#define MADDDISCIPLINEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtSql>

namespace Ui {
class mAddDisciplineDialog;
}

class mAddDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddDisciplineDialog(QWidget *parent = 0);
    ~mAddDisciplineDialog();

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);

signals:
    void cortegeFormed(QList<QVariant> &);

private:
    Ui::mAddDisciplineDialog *ui;
};

#endif // MADDDISCIPLINEDIALOG_H

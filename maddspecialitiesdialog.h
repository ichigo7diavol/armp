#ifndef MADDSPECIALITIESDIALOG_H
#define MADDSPECIALITIESDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class mAddSpecialitiesDialog;
}

class mAddSpecialitiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddSpecialitiesDialog(QWidget *parent = 0);
    ~mAddSpecialitiesDialog();

signals:
    void cortegeFormed(QList<QVariant>&);

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);

private:
    Ui::mAddSpecialitiesDialog *ui;
};

#endif // MADDSPECIALITIESDIALOG_H

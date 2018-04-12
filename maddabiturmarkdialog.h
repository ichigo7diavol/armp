#ifndef MADDABITURMARKDIALOG_H
#define MADDABITURMARKDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QLabel>
#include <QValidator>
#include <QMap>

#include "precompileconstants.h"

namespace Ui {
class mAddAbiturMarkDialog;
}

class mAddAbiturMarkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddAbiturMarkDialog(QWidget *parent = 0, int nri = 0);
    ~mAddAbiturMarkDialog();

public slots:
    void fillCortege(const int ri);
    void formCortege();

    void nextPage();
    void prevPage();

    void textChanged(const QString & newText);

signals:
    void cortegeFormed(QList<QVariant> &);

private:
    void visualize();

    Ui::mAddAbiturMarkDialog *ui;

    int cp; // current page
    int ri; // reg id

    QSqlTableModel * ptm;
    QSqlTableModel * pamtm;

    QVector<QLabel*> labv;
    QVector<QLineEdit*> linev;

    QMap<int,int> map;
};

#endif // MADDABITURMARKDIALOG_H

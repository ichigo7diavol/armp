#ifndef MENTRYDIALOG_H
#define MENTRYDIALOG_H

#include <QDialog>
#include <QFlags>
#include <QtSql>
#include <QMessageBox>

#include <precompileconstants.h>

namespace Ui {
class mEntryDialog;
}

class mEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mEntryDialog(QWidget *parent = 0);
    ~mEntryDialog();

public slots:
    void dbConnect();

signals:
    void dbConnected();

private:
    Ui::mEntryDialog *ui;
};

#endif // MENTRYDIALOG_H

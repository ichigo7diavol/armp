#ifndef MADDBENIFITDIALOG_H
#define MADDBENIFITDIALOG_H

#include <QDialog>

namespace Ui {
class mAddBenifitDialog;
}

class mAddBenifitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddBenifitDialog(QWidget *parent = 0);
    ~mAddBenifitDialog();

private:
    Ui::mAddBenifitDialog *ui;
};

#endif // MADDBENIFITDIALOG_H

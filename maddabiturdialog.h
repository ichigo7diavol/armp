#ifndef MADDABITURDIALOG_H
#define MADDABITURDIALOG_H

#include <QDialog>

namespace Ui {
class mAddAbiturDialog;
}

class mAddAbiturDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddAbiturDialog(QWidget *parent = 0);
    ~mAddAbiturDialog();

private:
    Ui::mAddAbiturDialog *ui;
};

#endif // MADDABITURDIALOG_H

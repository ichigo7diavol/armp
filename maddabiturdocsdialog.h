#ifndef ADDABITURDOCSDIALOG_H
#define ADDABITURDOCSDIALOG_H

#include <QDialog>

namespace Ui {
class mAddAbiturDocsDialog;
}

class mAddAbiturDocsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddAbiturDocsDialog(QWidget *parent = 0);
    ~mAddAbiturDocsDialog();

private:
    Ui::mAddAbiturDocsDialog *ui;
};

#endif // ADDABITURDOCSDIALOG_H

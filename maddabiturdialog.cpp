#include "maddabiturdialog.h"
#include "ui_maddabiturdialog.h"

mAddAbiturDialog::mAddAbiturDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddAbiturDialog)
{
    ui->setupUi(this);
}

mAddAbiturDialog::~mAddAbiturDialog()
{
    delete ui;
}

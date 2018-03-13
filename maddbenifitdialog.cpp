#include "maddbenifitdialog.h"
#include "ui_maddbenifitdialog.h"

mAddBenifitDialog::mAddBenifitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddBenifitDialog)
{
    ui->setupUi(this);
}

mAddBenifitDialog::~mAddBenifitDialog()
{
    delete ui;
}

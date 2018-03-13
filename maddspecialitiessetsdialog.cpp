#include "maddspecialitiessetsdialog.h"
#include "ui_maddspecialitiessetsdialog.h"

mAddSpecialitiesSetsDialog::mAddSpecialitiesSetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddSpecialitiesSetsDialog)
{
    ui->setupUi(this);
}

mAddSpecialitiesSetsDialog::~mAddSpecialitiesSetsDialog()
{
    delete ui;
}

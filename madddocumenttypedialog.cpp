#include "madddocumenttypedialog.h"
#include "ui_madddocumenttypedialog.h"

mAddDocumentTypeDialog::mAddDocumentTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddDocumentTypeDialog)
{
    ui->setupUi(this);
}

mAddDocumentTypeDialog::~mAddDocumentTypeDialog()
{
    delete ui;
}

#include "mabiturtable.h"
#include "ui_mabiturtable.h"

mAbiturTable::mAbiturTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mAbiturTable)
{
    ui->setupUi(this);
}

mAbiturTable::~mAbiturTable()
{
    delete ui;
}

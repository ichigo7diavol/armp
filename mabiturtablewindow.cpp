#include "mabiturtablewindow.h"
#include "ui_mabiturtablewindow.h"

mAbiturTableWindow::mAbiturTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mAbiturTableWindow)
{
    ui->setupUi(this);
}

mAbiturTableWindow::~mAbiturTableWindow()
{
    delete ui;
}

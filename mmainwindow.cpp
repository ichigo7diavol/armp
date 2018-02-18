#include "mmainwindow.h"
#include "ui_mmainwindow.h"


mMainWindow::mMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mMainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("АРМ Приемная комиссия"));

    QStringList menuTitles;
    menuTitles << "Файл" << "Вид" << "Справочники" << "Отчеты" << "Документы" << "Сервис" << "Окно" << "Справка";
    QString tmp;
    foreach (tmp, menuTitles) {
        ui->menuBar->addMenu(tmp);
    }

}

mMainWindow::~mMainWindow()
{
    delete ui;
}

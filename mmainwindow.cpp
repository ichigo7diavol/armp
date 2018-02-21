#include "mmainwindow.h"
#include "ui_mmainwindow.h"


mMainWindow::mMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mMainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("АРМ Приемная комиссия"));

    QMenu * pm;
    QList <QAction*> lpa; // list ptr action
    QAction * pa; // ptr action

    // ПУНКТ ФАЙЛ

    pm = ui->menuBar->addMenu("Файл");

    pa = new QAction("Начать новый набор");
    lpa << pa;

    pa = new QAction("Выбрать существующий набор");
    lpa << pa;

    pa = new QAction();
    pa->setSeparator(true);
    lpa << pa;

    pa = new QAction("Выход");
    this->connect(pa, SIGNAL(triggered()), SLOT(close()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ ВИД

    pm = ui->menuBar->addMenu("Вид");

    pa = new QAction("Панель инструментов");
    pa->setCheckable(true);
    pa->setChecked(true);
    ui->mainToolBar->connect(pa, SIGNAL(toggled(bool)), SLOT(setVisible(bool)));
    lpa << pa;

    pa = new QAction("Статус строка");
    pa->setCheckable(true);
    pa->setChecked(true);
    ui->statusBar->connect(pa, SIGNAL(toggled(bool)), SLOT(setVisible(bool)));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ СПРАВОЧНИКИ

    pm = ui->menuBar->addMenu("Справочники");
    pa = new QAction("Абитуриенты");
    lpa << pa;
    pa = new QAction("Учреждение");
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ ДОКУМЕНТЫ

    pm = ui->menuBar->addMenu("Документы");
    pa = new QAction("Экзаменационные ведомости");
    lpa << pa;
    pa = new QAction("Зачисление");
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ СЕРВИС

    pm = ui->menuBar->addMenu("Сервис");
    pa = new QAction("Параметры");
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ ОКНО

    pm = ui->menuBar->addMenu("Окно");
    pa = new QAction("Расположить каскадом");
    ui->mdiArea->connect(pa, SIGNAL(triggered(bool)), SLOT(cascadeSubWindows()));
    lpa << pa;

    pa = new QAction("Расположить мазайкой");
    ui->mdiArea->connect(pa, SIGNAL(triggered(bool)), SLOT(tileSubWindows()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();
}

mMainWindow::~mMainWindow()
{
    delete ui;
}

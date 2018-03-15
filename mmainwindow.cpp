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
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openAbiturientsTable()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();
    pm->addSeparator();

    pa = new QAction("Дисциплины");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openDisciplineTable()));
    lpa << pa;

    pa = new QAction("Льготы");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openBenefitsTable()));
    lpa << pa;

    pa = new QAction("Специальности");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openSpecialitiesTable()));
    lpa << pa;

    pa = new QAction("Контрольные цифры приема");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openSpecialitiesSetsTable()));
    lpa << pa;

    pa = new QAction("Типы документов");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openDocumentTypesTable()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ ДОКУМЕНТЫ

    pm = ui->menuBar->addMenu("Документы");
    //pa = new QAction("Экзаменационные ведомости");
    //lpa << pa;
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

void mMainWindow::openAbiturientsTable() {

    if (!findChild<mAbiturTableWindow*>(QString("mAbiturTableWindow"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new mAbiturTableWindow());

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Абитуриенты"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "mAbiturTableWindow is already opened!";
    }
}

void mMainWindow::openDisciplineTable() {

    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowDisciplines"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::disciplines));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Дисциплины"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "otherTablesWindow[Disciplines] is already opened!";
    }
}

void mMainWindow::openBenefitsTable() {
    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowBenefits"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::benefits));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Льготы"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "otherTablesWindow[Benefits] is already opened!";
    }
}

void mMainWindow::openSpecialitiesTable() {
    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowSpecialities"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::specialities));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Специальности"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "otherTablesWindow[Specialities] is already opened!";
    }
}

void mMainWindow::openSpecialitiesSetsTable() {

}

void mMainWindow::openDocumentTypesTable() {

}

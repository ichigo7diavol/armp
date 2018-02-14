#include "mmainwindow.h"
#include "ui_mmainwindow.h"


mMainWindow::mMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mMainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("АРМ Приемная комиссия"));

    srand(time(NULL));

    QAction * pa1 = new QAction();

    pa1->setIcon(QIcon(":/icons/TablesheetIcon32.png"));
    ui->mainToolBar->addAction(pa1);
    pasw = new QMainWindow();
    pastm = new QSqlTableModel();
    pastm->setTable(QString("persons"));
    pastm->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    pastm->select();

    patv = new QTableView();
    patv->setModel(pastm);
    pasw->setCentralWidget(patv);
    ui->mdiArea->addSubWindow(pasw);
    qDebug() << pastm->primaryKey();

    QObject::connect(pa1, QAction::triggered, this, mMainWindow::randomSecondName);
}

mMainWindow::~mMainWindow()
{
    delete ui;
}

void mMainWindow::randomSecondName() {

    QMessageBox msgBox;
    msgBox.setText(pastm->data(pastm->index(rand()%pastm->rowCount(),1)).toString());
    pastm->data(pastm->index(rand()%pastm->rowCount()-1,0)).toString();
    msgBox.exec();
}

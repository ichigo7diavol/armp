#include "mabiturtablewindow.h"
#include "ui_mabiturtablewindow.h"

mAbiturTableWindow::mAbiturTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mAbiturTableWindow)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    ptm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
    ptm->setEditStrategy(QSqlTableModel::OnRowChange);
    ptm->setTable("entrants");
    ptm->setRelation(7, QSqlRelation("benefits", "id", "benefit_name"));
    ptm->select();


    QList<QString> tsl;
    tsl << "Регистрационный номер" << "Фамилия" << "Имя" << "Отчество" << "Дата регистрации" << "№ экз. листа" << "Зачислен" << "Льгота"
        << "Дата рождения" << "Пол" << "Гражданство" << "Телефон" << "Уровень образования" << "Год окончания" << "Средний балл"
        << "Нужда в общежитии" << "Примечание" << "Национальность" << "E-mail";
    QString ts;
    int counter = 0;
    foreach(ts, tsl) { ptm->setHeaderData(counter++, Qt::Horizontal, ts); }

    ui->abiturView->setModel(ptm);

    QFont tf(ui->abiturView->horizontalHeader()->font());
    tf.setPointSize(8);
    ui->abiturView->horizontalHeader()->setFont(tf);

    ui->toolBar->addAction(QIcon(":/icons/A"), "Добавить строку", this, SLOT(addRow()));
    ui->toolBar->addAction(new QAction(QIcon(":/icons/D"), "Удалить строку"));
    ui->toolBar->addAction(new QAction(QIcon(":/icons/E"), "Изменить строку"));
    ui->toolBar->addAction(new QAction(QIcon(":/icons/C"), "Копировать строку"));

    qDebug() << this->objectName();
}

mAbiturTableWindow::~mAbiturTableWindow()
{
    qDebug() << "Entrants view's and model's deleted!";

    delete ui;
}

void mAbiturTableWindow::addRow() {

    mAddAbiturDialog * tmp = new mAddAbiturDialog;
    tm.p->exec();

    //qDebug() << ptm->submitAll();
    //qDebug() << ptm->lastError().text();
}

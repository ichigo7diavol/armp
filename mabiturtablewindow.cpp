
#include "mabiturtablewindow.h"
#include "ui_mabiturtablewindow.h"

mAbiturTableWindow::mAbiturTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mAbiturTableWindow),
    av()
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    ptm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
    ptm->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ptm->setTable("entrants");
    ptm->setRelation(ptm->fieldIndex(QString(DefF_BenId)), QSqlRelation("benefits", "id", "name"));
    ptm->select();

    // reg_num, reg_date, sec_name, name, mid_name, birth_date, citizenship, phone_number, email,
    // avg_score, benefit_id, is_dormitory, is_enlisted, gender, educ_lvl (нескрытые стобцы)

    // reg_adr, live_adr, end_educ_year, is_rules_agreed, is_date_agreed, is_first_spo, is_data_proc_agreed,
    // note (скрытые столбцы)

    // sec_id (скрытый + добавляется отдельной формой)

    av /*<< new QString(DefF_RegNum)*/ << new QString(DefF_RegDate)
       << new QString(DefF_SecName) << new QString(DefF_Name)
       << new QString(DefF_MidName) << new QString(DefF_BirthDate)
       << new QString(DefF_CitShip) << new QString(DefF_PhonNum)
       << new QString(DefF_Email) << new QString(DefF_AvgScr)
       << new QString(DefF_BenId) << new QString(DefF_IsDorm)
       << new QString(DefF_IsEnlstd) << new QString(DefF_Gender)
       << new QString(DefF_EducLvl)

       << new QString(DefF_RegAdr) << new QString(DefF_LivAdr)
       << new QString(DefF_EndEdYear) << new QString(DefF_IsRules)
       << new QString(DefF_IsDate) << new QString(DefF_IsSPO)
       << new QString(DefF_IsProc) << new QString(DefF_Note);

    /*
    QList<QString> tsl;

    tsl << "Регистрационный номер" << "Фамилия" << "Имя" << "Отчество" << "Дата регистрации" << "№ экз. листа" << "Зачислен" << "Льгота"
        << "Дата рождения" << "Пол" ;//<< "Гражданство" << "Телефон" << "Уровень образования" << "Год окончания" << "Средний балл"
        //<< "Нужда в общежитии" << "Примечание" << "Национальность" << "E-mail";

    QString ts;

    int counter = 0;
    foreach(ts, tsl) { ptm->setHeaderData(counter++, Qt::Horizontal, ts); }
    //*/

    ui->abiturView->setModel(ptm);
    ui->abiturView->setColumnHidden(0,true);

    QFont tf(ui->abiturView->horizontalHeader()->font());
    tf.setPointSize(8);
    ui->abiturView->horizontalHeader()->setFont(tf);

    ui->toolBar->addAction(QIcon(":/icons/A"), "Добавить строку", this, SLOT(addRowButton()));
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

void mAbiturTableWindow::addRowButton() {

    mAddAbiturDialog * tmp = new mAddAbiturDialog;
    this->connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)), SLOT(addRow(QList<QVariant>&)));
    tmp->exec();
}

void mAbiturTableWindow::addRow(QList <QVariant> & lv) {

    QSqlRecord tmp (ptm->record());
    QVariant tmpv;
    tmp.setGenerated(0, false);
    int counter = 0;
    foreach(tmpv, lv) {
        qDebug() << *(av[counter]);
        tmp.setValue(tmp.indexOf(*(av[counter])), tmpv);
        tmp.setGenerated(tmp.indexOf(*(av[counter])) ,true);
        counter++;
    }
    //qDebug() << tmp.indexOf("benefits_name_2");
    tmp.setValue(tmp.indexOf(QString("benefits_name_2")), 1);
    tmp.setGenerated(tmp.indexOf(QString("benefits_name_2")), 1);

    ptm->insertRecord(-1,tmp);

    if (ptm->submitAll()) {
        QMessageBox::information(this, "Добавление строки.", "Добавление строки прошло успешно");
        ptm->select();
    }
    else {
        QMessageBox::warning(this, "Добавление строки", "Введенные данные были некорректны!");
        qDebug() << "Adding the row goes wrong!" << ptm->lastError().text();
        ptm->revertAll();
    }
}

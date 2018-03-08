
#include "mabiturtablewindow.h"
#include "ui_mabiturtablewindow.h"

mAbiturTableWindow::mAbiturTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mAbiturTableWindow),
    av(),
    cfh()
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    ptm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
    ptm->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ptm->setTable("entrants_v");
    ptm->setRelation(ptm->fieldIndex(QString(DefF_BenId)), QSqlRelation(DefF_EntrantsFTbl,
                                                                        DefF_EntrantsBenFKPK,
                                                                        DefF_EntrantsBenFAtr));
    ptm->select();

    // reg_num, reg_date, sec_name, name, mid_name, birth_date, citizenship, phone_number, email,
    // avg_score, benefit_id, is_dormitory, is_enlisted, gender, educ_lvl (нескрытые стобцы)

    cfh << new QString(DefF_RegNum) << new QString(DefF_RegAdr) << new QString(DefF_LivAdr) << new QString(DefF_EndEdYear)
        << new QString(DefF_IsRules) << new QString(DefF_IsDate) << new QString(DefF_IsSPO)
        << new QString(DefF_IsProc) << new QString(DefF_Note) << new QString(DefF_SetId);

    QString * ts;

    // reg_adr, live_adr, end_educ_year, is_rules_agreed, is_date_agreed, is_first_spo, is_data_proc_agreed,
    // note (скрытые столбцы)

    // sec_id (скрытый + добавляется отдельной формой)

    av /*<< new QString(DefF_RegNum)*/ << new QString(DefF_RegDate)
       << new QString(DefF_SecName) << new QString(DefF_Name)
       << new QString(DefF_MidName) << new QString(DefF_BirthDate)
       << new QString(DefF_CitShip) << new QString(DefF_PhonNum)
       << new QString(DefF_Email) << new QString(DefF_AvgScr)
       << new QString(/*DefF_BenId*/ DefF_EntrantsBenFAtr) << new QString(DefF_IsDorm)
       << new QString(DefF_IsEnlstd) << new QString(DefF_Gender)
       << new QString(DefF_EducLvl)

       << new QString(DefF_RegAdr) << new QString(DefF_LivAdr)
       << new QString(DefF_EndEdYear) << new QString(DefF_IsRules)
       << new QString(DefF_IsDate) << new QString(DefF_IsSPO)
       << new QString(DefF_IsProc) << new QString(DefF_Note);

    QList<QString> tsl;

    QString ts2;

    tsl << "Дата регистрации" << "Фамилия" << "Имя" << "Отчество" << "Дата рождения" << "Гражданство" << "Номер телефона"
        << "Email" << "Средний балл" << "Льгота" << "Необходимость в общежитии" << "Зачислен"
        << "Пол" << "Уровень образования";

    int counter = 1;
    foreach(ts2, tsl) { ptm->setHeaderData(counter++, Qt::Horizontal, ts2); }

    ui->abiturView->setModel(ptm);
    foreach (ts, cfh) { ui->abiturView->setColumnHidden(ptm->fieldIndex(*ts), true); }

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

    QSqlRecord tr (ptm->record());
    QVariant tv;
    int counter = 0;

    tr.setGenerated(counter, false);

    foreach(tv, lv) {
        tr.setValue(tr.indexOf(*(av[counter])), tv);
        tr.setGenerated(tr.indexOf(*(av[counter])) ,true);
        counter++;
    }

    ptm->insertRecord(-1,tr);

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

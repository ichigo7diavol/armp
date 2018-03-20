
#include "mabiturtablewindow.h"
#include "ui_mabiturtablewindow.h"

mAbiturTableWindow::mAbiturTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mAbiturTableWindow),
    pstm(NULL),
    ppstm(NULL)
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
    ui->abiturView->setSortingEnabled(true);
    ptm->setSort(2, Qt::AscendingOrder);
    ptm->select();

    pptm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pptm->setEditStrategy(QSqlTableModel::OnRowChange);
    pptm->setTable("entrants_v");
    pptm->select();

    QVector <QString> cfs; // columns for showing
    QVector <QString> cfh; // columns for hide

    // reg_num, reg_date, sec_name, name, mid_name, birth_date, citizenship, phone_number, email,
    // avg_score, benefit_id, is_dormitory, is_enlisted, gender, educ_lvl (нескрытые стобцы)

    cfh << DefF_RegNum << DefF_RegAdr << DefF_LivAdr << DefF_EndEdYear
        << DefF_IsRules << DefF_IsDate << DefF_IsSPO
        << DefF_IsProc << DefF_Note << DefF_SetId;

    // reg_adr, live_adr, end_educ_year, is_rules_agreed, is_date_agreed, is_first_spo, is_data_proc_agreed,
    // note (скрытые столбцы)

    // sec_id (скрытый + добавляется отдельной формой)

    cfs << DefF_RegDate
       << DefF_SecName << DefF_Name
       << DefF_MidName << DefF_BirthDate
       << DefF_CitShip << DefF_PhonNum
       << DefF_Email << DefF_AvgScr
       << DefF_EntrantsBenFAtr << DefF_IsDorm
       << DefF_IsEnlstd << DefF_Gender
       << DefF_EducLvl

       << DefF_RegAdr << DefF_LivAdr
       << DefF_EndEdYear << DefF_IsRules
       << DefF_IsDate << DefF_IsSPO
       << DefF_IsProc << DefF_Note;

    QList<QString> hsl; // headers string list

    hsl << "Дата регистрации" << "Фамилия" << "Имя" << "Отчество" << "Дата рождения" << "Гражданство" << "Номер телефона"
        << "Email" << "Средний балл" << "Льгота" << "Необходимость в общежитии" << "Зачислен"
        << "Пол" << "Уровень образования";

    QString ts;

    ui->abiturView->setModel(ptm);
    foreach (ts, cfh) {
        hci.push_back(int(ptm->fieldIndex(ts)));
        ui->abiturView->setColumnHidden(hci.back(), true);
    }

    foreach(ts, cfs) {
        sci.push_back(int(ptm->fieldIndex(ts)));
    }

    int i = 0;
    foreach (ts, hsl) { ptm->setHeaderData(sci[i++], Qt::Horizontal, ts); }

    QFont tf(ui->abiturView->horizontalHeader()->font());
    tf.setPointSize(8);
    ui->abiturView->horizontalHeader()->setFont(tf);

    ui->toolBar->addAction(QIcon(":/icons/A"), "Добавить строку", this, SLOT(addRowButton()));
    ui->toolBar->addAction(QIcon(":/icons/D"), "Удалить строку", this, SLOT(deleteRowButton()));
    ui->toolBar->addAction(QIcon(":/icons/E"), "Изменить строку", this, SLOT(editRowButton()));
    ui->toolBar->addAction(QIcon(":/icons/C"), "Копировать строку", this, SLOT(copyRowButton()));

    tableSwitcher = new QComboBox(this);
    tableSwitcher->addItem("Экзамены");
    tableSwitcher->addItem("Документы");
    tableSwitcher->addItem("Спциальности");
    tableSwitcher->addItem("Оценки аттестата");

    QObject::connect(tableSwitcher, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeSubTable(int)));

    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(tableSwitcher);

    tableSwitcher->setCurrentIndex(1);

    qDebug() << "mAbiturTableWindow created!";
}

mAbiturTableWindow::~mAbiturTableWindow()
{
    qDebug() << "Entrants view's and model's deleted!";

    delete ui;
}

void mAbiturTableWindow::addRowButton() {

    QDialog * tmp;
    print();
    if (this->focusWidget() != ui->abiturView) {
        if (ptm->rowCount() == 0) {
            QMessageBox::warning(this, "Ошибка", "Для добавление подзаписи, кол-во абитуриентов должно быть больше одного!");
            return;
        }
        else
            switch (swt) {
            case exams:
                tmp = new mAddExamDialog;
                break;
            case documents:
                tmp = new mAddAbiturDocsDialog;
                break;
            case specialities:
                tmp = new mAddSpecDialog;
                break;
            case marks:
                tmp = new mAddAbiturMarkDialog;
                break;
            }

        this->connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)), SLOT(addRow(QList<QVariant>&)));
        tmp->exec();

        return;
    }

    tmp = new mAddAbiturDialog;
    this->connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)), SLOT(addRow(QList<QVariant>&)));
    tmp->exec();
}

void mAbiturTableWindow::addRow(QList <QVariant> & lv) {

    bool f = this->focusWidget() != ui->abiturView;
    QSqlRecord tr (f ? ppstm->record() : pptm->record());
    QVariant tv;
    int counter = 0;

    if (f) {
        QList<QVariant>::iterator it = lv.begin();

        switch (swt){
        case exams: {
            tr.setGenerated(3, false);
            tr.setValue("reg_num", ptm->record(ui->abiturView->currentIndex().row())
                        .value("reg_num"));
            QList<QVariant>::iterator it = lv.begin();
            tr.setValue("score", (*(it++)).toString());
            tr.setValue("discipline_id", (*(it++)).toString());
            tr.setValue("exam_type", (*(it++)).toString());
            qDebug() << tr;
            }
            break;
        case specialities: {
            QSqlTableModel ttm(this, QSqlDatabase::database(QString(DBName)));
            ttm.setTable(QString("specialities_sets"));
            ttm.setFilter(QString("spec_id = %3 and educ_form = '%2' and finance_form = '%1'")
                          .arg((*(it++)).toString())
                          .arg((*(it++)).toString())
                          .arg((*(it++)).toString()));
            ttm.select();
            tr.setValue("set_id",ttm.record(0).value("set_id").toInt());
            tr.setValue("reg_num", ptm->record(ui->abiturView->currentIndex().row())
                        .value("reg_num"));
            tr.setGenerated("priority", false);
            }
            break;
        case documents: {
            tr.setGenerated("document_id", false);
            tr.setValue("reg_num", ptm->record(ui->abiturView->currentIndex().row())
                        .value("reg_num"));
            QList<QVariant>::iterator it = lv.begin();
            tr.setValue("document_type_id", (*(it++)));
            tr.setValue("number", (*(it++)));
            tr.setValue("series", (*(it++)));
            tr.setValue("date", (*(it++)));
            tr.setValue("issued_by", (*(it++)));
            tr.setValue("count", (*(it++)));
            tr.setValue("is_copy", (*(it++)));
            tr.setValue("is_issued", (*(it++)));
            }
            break;
        case marks: {
            tr.setValue("reg_num", ptm->record(ui->abiturView->currentIndex().row())
                        .value("reg_num"));
            tr.setValue("discipline_id", (*(it++)));
            tr.setValue("mark", (*(it++)));
            }
            break;
        }
    }
    else {
        tr.setGenerated(counter, false);

        foreach(tv, lv) {
            tr.setValue(sci[counter], tv);
            tr.setGenerated(sci[counter++] ,true);
        }
    }

    if ((f ? ppstm : pptm)->insertRecord(-1,tr)) {
        QMessageBox::information(this, "Добавление строки", "Добавление строки прошло успешно");
        (f ? pstm : ptm)->select();
    }
    else {
        QMessageBox::warning(this, "Добавление строки", "Введенные данные были некорректны!");
        qDebug() << "Adding the row goes wrong!" << (f ? ppstm : pptm)->lastError().text();
        (f ? ppstm : pptm)->revertAll();
    }
}

void mAbiturTableWindow::deleteRowButton() {    

    bool f = this->focusWidget() != ui->abiturView;

    if (f ? ppstm->rowCount() == 0 : pptm->rowCount() == 0) {
        return;
    }

    if (f) {
        switch (swt){

        case exams:
            ppstm->setFilter(QString("reg_num = %1 AND exam_data_id = %2")
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("reg_num").toString())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("exam_data_id").toString()));
            break;
        case documents:
            ppstm->setFilter(QString("reg_num = %1 AND document_id = %2")
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("reg_num").toString())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("document_id").toString()));
            break;
        case specialities:
            ppstm->setFilter(QString("reg_num = %1 and set_id = %2")
                             .arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row()).value(1).toInt()));
            break;
        case marks:
            ppstm->setFilter(QString("reg_num = %1 and discipline_id = %2")
                             .arg(ptm->record(ui->abiturView->currentIndex().row()).value("reg_num").toInt())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row()).value("discipline_id").toInt()));
            break;
        }
        ppstm->removeRow(0);
    }
    else {
        pptm->setFilter(QString("reg_num = %1").arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt()));
        pptm->removeRow(0);
    }

    if (f ? ppstm->submitAll() : pptm->submitAll()) {
        QMessageBox::information(this, "Удаление строки", "Удаление строки прошло успешно");
        (f ? pstm : ptm)->select();
    }
    else {
        QMessageBox::warning(this, "Удаление строки", "Ошибка во время удаления!");
        qDebug() << "Deleting the row goes wrong!" << (f ? ppstm->lastError().text() : pptm->lastError().text());
        (f ? ppstm : pptm)->revertAll();
    }
}

void mAbiturTableWindow::editRowButton() {

    bool f = this->focusWidget() != ui->abiturView;

    if (f ? pstm->rowCount() == 0 : pptm->rowCount() == 0) {
        return;
    }

    QDialog * tmp = NULL;

    if (f) {
        switch (swt){

        case exams:
            tmp = new mAddExamDialog;
            ((mAddExamDialog*)tmp)->fillCortege(pstm->record(ui->subTablesView->currentIndex().row()));
            break;
        case documents:
            tmp = new mAddAbiturDocsDialog;
            ((mAddAbiturDocsDialog*)tmp)->fillCortege(pstm->record(ui->subTablesView->currentIndex().row()));
            break;
        case specialities:
            tmp = new mAddSpecDialog;
            ((mAddSpecDialog*)tmp)->fillCortege(pstm->record(ui->subTablesView->currentIndex().row()));
            break;
        case marks:
            tmp = new mAddAbiturMarkDialog;
            ((mAddAbiturMarkDialog*)tmp)->fillCortege(pstm->record(ui->subTablesView->currentIndex().row()));
            break;
        }

    }
    else {
        tmp = new mAddAbiturDialog;
        ((mAddAbiturDialog*)tmp)->fillCortege(ptm->record(ui->abiturView->currentIndex().row()), sci);
    }

    this->connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)), SLOT(editRow(QList<QVariant>&)));

    tmp->exec();
}

void mAbiturTableWindow::editRow(QList <QVariant> & lv) {

    bool f = this->focusWidget() != ui->abiturView;

    QSqlRecord tr ((f ? ppstm : pptm)->record());
    QVariant tv;

    int counter = 0;

    if (f) {
        QList<QVariant>::iterator it = lv.begin();

        switch (swt){
        case specialities: {
            QSqlTableModel ttm(this, QSqlDatabase::database(QString(DBName)));
            ttm.setTable(QString("specialities_sets"));
            ttm.setFilter(QString("spec_id = %3 and educ_form = '%2' and finance_form = '%1'")
                          .arg((*(it++)).toString())
                          .arg((*(it++)).toString())
                          .arg((*(it++)).toString()));
            ttm.select();

            tr.setValue("set_id",ttm.record(0).value("set_id").toInt());

            tr.setValue("reg_num", ptm->record(ui->abiturView->currentIndex().row())
                        .value("reg_num"));
            ppstm->setFilter(QString("reg_num = %1 AND set_id = %2")
                             .arg(tr.value("reg_num").toString())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("set_id").toString()));
            }
            break;
        case exams: {
            ppstm->setFilter(QString("reg_num = %1 AND exam_data_id = %2")
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("reg_num").toString())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("exam_data_id").toString()));
            tr.setGenerated(0, false);
            tr.setGenerated(3, false);
            tr.setValue("score", (*(it++)).toString());
            tr.setValue("discipline_id", (*(it++)).toString());
            tr.setValue("exam_type", (*(it++)).toString());
            }
            break;
        case documents: {
            ppstm->setFilter(QString("reg_num = %1 AND document_id = %2")
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("reg_num").toString())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("document_id").toString()));
            QList<QVariant>::iterator it = lv.begin();
            tr.setGenerated(0,false);
            tr.setGenerated(8,false);
            tr.setValue("document_type_id", (*(it++)).toString());
            tr.setValue("number", (*(it++)).toString());
            tr.setValue("series", (*(it++)).toString());
            tr.setValue("date", (*(it++)).toDate());
            tr.setValue("issued_by", (*(it++)).toString());
            tr.setValue("count", (*(it++)).toString());
            tr.setValue("is_copy", (*(it++)).toString());
            tr.setValue("is_issued", (*(it++)).toString());
            }
            break;
        case marks: {
            ppstm->setFilter(QString("reg_num = %1 AND discipline_id = %2")
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("reg_num").toString())
                             .arg(pstm->record(ui->subTablesView->currentIndex().row())
                                  .value("discipline_id").toString()));
            tr.setValue("reg_num", ptm->record(ui->abiturView->currentIndex().row())
                        .value("reg_num"));
            tr.setValue("discipline_id", (*(it++)));
            tr.setValue("mark", (*(it++)));
            }
            break;
        }
        ppstm->select();
    }
    else {
        tr.setGenerated(counter, false);

        foreach(tv, lv) {
            qDebug() << sci[counter];
            tr.setValue(sci[counter], tv);
            tr.setGenerated(sci[counter++] ,true);
        }

        pptm->setFilter(QString("reg_num = %1")
                        .arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt()));
        pptm->select();
    }

    if ((f ? ppstm : pptm)->setRecord(0, tr)) {
        QMessageBox::information(this, "Изменение строки", "Изменение строки прошло успешно");
        (f ? pstm : ptm)->select();
    }
    else {
        QMessageBox::warning(this, "Изменение строки", "Введенные данные были некорректны!");
        qDebug() << "Editing the row goes wrong!" << (f ? ppstm : pptm)->lastError().text();
        (f ? ppstm : pptm)->revertAll();
    }
}

void mAbiturTableWindow::copyRowButton() {
    bool f = this->focusWidget() != ui->abiturView;

    if ((f ? ppstm : pptm)->rowCount() == 0) {
        return;
    }

    QSqlRecord tr;

    if (f) {
        switch (swt){

        case exams:
            QMessageBox::warning(this, "Ошибка", "Данный тип записи нельзя копировать!");
            return;
        case documents:
            QMessageBox::warning(this, "Ошибка", "Данный тип записи нельзя копировать!");
            return;
        case specialities:
            QMessageBox::warning(this, "Ошибка", "Данный тип записи нельзя копировать!");
            return;
        case specialities:
            QMessageBox::warning(this, "Ошибка", "Данный тип записи нельзя копировать!");
            return;
        }
    }
    else {
        pptm->setFilter(QString("reg_num = %1").arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt()));

        tr = pptm->record(0);
        tr.setGenerated(0, false);
    }

    if ((f ? ppstm : pptm)->insertRecord(-1, tr)) {
        QMessageBox::information(this, "Копирование строки", "Копирование строки прошло успешно");
        (f ? pstm : ptm)->select();
    }
    else {
        QMessageBox::warning(this, "Копирование строки", "Ошибка во время копирования!");
        qDebug() << "Copying the row goes wrong!" << (f ? ppstm : pptm)->lastError().text();
        (f ? ppstm : pptm)->revertAll();
    }
}

void mAbiturTableWindow::changeSubTable (int index) {

    if (pstm) {
        delete pstm;
        delete ppstm;
    }

    switch (swt) {
    case exams:
        ui->subTablesView->setColumnHidden(0, false);
        ui->subTablesView->setColumnHidden(3, false);
        break;

    case documents:
        ui->subTablesView->setColumnHidden(0, false);
        ui->subTablesView->setColumnHidden(8, false);
        break;

    case specialities:
        ui->subTablesView->setColumnHidden(0, false);
        ui->subTablesView->setColumnHidden(1, false);
        break;
    case marks:
        ui->subTablesView->setColumnHidden(0, false);
        ui->subTablesView->setColumnHidden(2, false);
        break;
    }

    switch (index) {
    case 0:
        qDebug() << "sub i = 0";
        pstm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
        pstm->setEditStrategy(QSqlTableModel::OnRowChange);
        pstm->setTable("exams");
        pstm->setRelation(2, QSqlRelation("disciplines", "discipline_id", "name"));

        pstm->setHeaderData(1, Qt::Horizontal, "Оценка / балл");
        pstm->setHeaderData(2, Qt::Horizontal, "Дисциплина");
        pstm->setHeaderData(4, Qt::Horizontal, "Тип экзамена");
        pstm->select();

        ppstm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
        ppstm->setTable("exams");
        ppstm->select();

        swt = exams;

        break;
    case 1:
        qDebug() << "sub i = 1";
        pstm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
        pstm->setEditStrategy(QSqlTableModel::OnRowChange);
        pstm->setTable("documents");
        pstm->setRelation(7, QSqlRelation("document_types", "document_type_id", "name"));

        pstm->setHeaderData(pstm->fieldIndex("series"), Qt::Horizontal, "Серия");
        pstm->setHeaderData(pstm->fieldIndex("number"), Qt::Horizontal, "Номер");
        pstm->setHeaderData(pstm->fieldIndex("date"), Qt::Horizontal, "Дата");
        pstm->setHeaderData(pstm->fieldIndex("issued_by"), Qt::Horizontal, "Кем получен");
        pstm->setHeaderData(pstm->fieldIndex("count"), Qt::Horizontal, "Кол-во");
        pstm->setHeaderData(pstm->fieldIndex("is_copy"), Qt::Horizontal, "Копия");
        pstm->setHeaderData(7, Qt::Horizontal, "Тип документа");
        pstm->setHeaderData(pstm->fieldIndex("is_issued"), Qt::Horizontal, "Выдан");

        pstm->select();

        ppstm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
        ppstm->setTable("documents");
        ppstm->select();

        swt = documents;

        break;
    case 2: {
        qDebug() << "sub i = 2";
        pstm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
        pstm->setEditStrategy(QSqlTableModel::OnRowChange);
        pstm->setTable("entrants_specs_v");
        pstm->setFilter(QString("reg_num = %1").arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt()));

        QList<QString> hsl; // headers string list

        hsl << "Оценка" << "Дисциплина";

        QString ts;
        int i = 2;
        foreach (ts, hsl) {
            pstm->setHeaderData(i++, Qt::Horizontal, ts);
        }

        pstm->select();

        ppstm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
        ppstm->setTable("entrants_specialities_sets");
        ppstm->select();

        swt = specialities;
        }
        break;
    case 3: {
        qDebug() << "sub i = 3";
        pstm = new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
        pstm->setEditStrategy(QSqlTableModel::OnRowChange);
        pstm->setTable("education_certificates_v");
        pstm->setFilter(QString("reg_num = %1").arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt()));

        pstm->setHeaderData(1, Qt::Horizontal, "Оценка");
        pstm->setHeaderData(3, Qt::Horizontal, "Дисциплина");

        pstm->select();

        ppstm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
        ppstm->setTable("education_certificates");
        ppstm->select();

        swt = marks;
        }
        break;
    }

    QObject::connect(ui->abiturView, SIGNAL(clicked(QModelIndex)),
                     this, SLOT(abiturChanged()));

    ui->subTablesView->setModel(pstm);

    switch (swt) {
    case exams:
        ui->subTablesView->setColumnHidden(0, true);
        ui->subTablesView->setColumnHidden(3, true);
        break;

    case documents:
        ui->subTablesView->setColumnHidden(0, true);
        ui->subTablesView->setColumnHidden(8, true);
        break;

    case specialities:
        ui->subTablesView->setColumnHidden(0, true);
        ui->subTablesView->setColumnHidden(1, true);
        break;
    case marks:
        ui->subTablesView->setColumnHidden(0, true);
        ui->subTablesView->setColumnHidden(2, true);
        break;
    }
}

void mAbiturTableWindow::abiturChanged() {

    pstm->setFilter(QString("reg_num = %1")
                    .arg(ptm->record(ui->abiturView->currentIndex().row()).value(0).toInt()));

    pstm->select();
}

void mAbiturTableWindow::print()
{
    QString filename="users.pdf";
    //Paramètres d'impression
    QPrinter printer;//QPrinter::HighResolution);
    printer.setOutputFileName(filename);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);

    QPainter painter(&printer);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    ui->abiturView->render( &painter );
    painter.end();
}

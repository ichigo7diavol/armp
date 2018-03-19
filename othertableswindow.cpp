#include "othertableswindow.h"
#include "ui_othertableswindow.h"

otherTablesWindow::otherTablesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::otherTablesWindow)
{
    ui->setupUi(this);
}

otherTablesWindow::otherTablesWindow(QWidget *parent,
                                     otherTablesWinTypes wt) :
    QMainWindow(parent),
    ui(new Ui::otherTablesWindow)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    ui->toolBar->addAction(QIcon(":/icons/A"), "Добавить строку", this, SLOT(addRowButton()));
    ui->toolBar->addAction(QIcon(":/icons/D"), "Удалить строку", this, SLOT(deleteRowButton()));
    ui->toolBar->addAction(QIcon(":/icons/E"), "Изменить строку", this, SLOT(editRowButton()));
    ui->toolBar->addAction(QIcon(":/icons/C"), "Копировать строку");// this, SLOT(copyRowButton()));


    ptm = new QSqlRelationalTableModel(this, QSqlDatabase::database(DBName));
    pptm = new QSqlTableModel(this, QSqlDatabase::database(DBName));

    switch (wt){
    case disciplines: {
        setObjectName("otherTablesWindowDisciplines");
        ct = disciplines;

        ptm->setTable("disciplines");
        pptm->setEditStrategy(QSqlTableModel::OnRowChange);
        pptm->setTable("disciplines");

        ui->otherTablesView->setModel(ptm);
        ptm->select();

        ui->otherTablesView->setColumnHidden(0,true);
        ui->otherTablesSubView->setVisible(false);

        ptm->setHeaderData(1, Qt::Horizontal, "Наименование дисциплины");
        }
        break;
    case benefits: {
        setObjectName("otherTablesWindowBenefits");
        ct = benefits;

        ptm->setTable("benefits");
        pptm->setTable("benefits");

        ui->otherTablesView->setModel(ptm);
        ptm->select();

        ui->otherTablesView->setColumnHidden(0,true);
        ui->otherTablesSubView->setVisible(false);

        ptm->setHeaderData(1, Qt::Horizontal, "Наименование льготы");
        ptm->setHeaderData(2, Qt::Horizontal, "Освобождение от вступительных");
        ptm->setHeaderData(3, Qt::Horizontal, "Освобождение от конкурса");
    }
    break;
    case specialities_sets: {
        setObjectName("otherTablesWindowSpecialitiesSets");
        ct = specialities_sets;

        ptm->setTable("specialities_sets");
        pptm->setTable("specialities_sets");

        ptm->setRelation(1, QSqlRelation("specialities", "spec_id", "name"));

        ui->otherTablesView->setModel(ptm);
        ptm->select();

        ui->otherTablesView->setColumnHidden(0,true);

        ptm->setHeaderData(1, Qt::Horizontal, "Специальность");
        ptm->setHeaderData(2, Qt::Horizontal, "Форма обучения");
        ptm->setHeaderData(3, Qt::Horizontal, "Отделение");
        ptm->setHeaderData(4, Qt::Horizontal, "Количество мест");
        ptm->setHeaderData(5, Qt::Horizontal, "Год");

        ui->otherTablesSubView->setVisible(false);

    }
    break;
    case specialities: {
        setObjectName("otherTablesWindowSpecialities");
        ct = specialities;

        ptm->setTable("specialities");
        pptm->setTable("specialities");

        ui->otherTablesView->setModel(ptm);
        ptm->select();

        ui->otherTablesView->setColumnHidden(0,true);
        ui->otherTablesSubView->setVisible(true);

        ptm->setHeaderData(1, Qt::Horizontal, "Наименование");
        ptm->setHeaderData(2, Qt::Horizontal, "Код");
        ptm->setHeaderData(3, Qt::Horizontal, "Сокращение");

        pstm = new QSqlRelationalTableModel(this, QSqlDatabase::database(DBName));
        ppstm = new QSqlTableModel(this, QSqlDatabase::database(DBName));

        ui->toolBar->addSeparator();

        specComboBox = new QComboBox(this);
        specComboBox->addItem("Профильный предмет");
        specComboBox->addItem("Обязательынй экзамен");

        QObject::connect(specComboBox , SIGNAL(currentIndexChanged(int)),
                         this, SLOT(specComboBoxChanged(int)));

        ui->toolBar->addWidget(specComboBox );

        specComboBoxChanged(0);
    }
    break;
    case document_types: {
        setObjectName("otherTablesWindowDocumentTypes");
        ct = document_types;

        ptm->setTable("document_types");
        pptm->setTable("document_types");

        ui->otherTablesView->setModel(ptm);
        ptm->select();

        ui->otherTablesView->setColumnHidden(0,true);
        ui->otherTablesSubView->setVisible(false);

        ptm->setHeaderData(ptm->fieldIndex("name"), Qt::Horizontal, "Наименование");
        ptm->setHeaderData(ptm->fieldIndex("is_contest"), Qt::Horizontal, "Участие в конкурсе");
        ptm->setHeaderData(ptm->fieldIndex("is_mandatory"), Qt::Horizontal, "Является обязательным");
    }
    break;
    }
}

otherTablesWindow::~otherTablesWindow()
{
    qDebug() << "otherTablesWindow deleted";

    delete ui;
}

void otherTablesWindow::addRowButton() {

    bool f = focusWidget() != ui->otherTablesView ? true : false;

    QDialog * tmp;

    if (f) {
        if (specComboBox->currentIndex() == 0)
            tmp = new mSpecSetDiscAddDialog;
        else
            tmp = new mAddExamDialog;
    }
    else
        switch (ct) {
        case disciplines: {
            tmp = new mAddDisciplineDialog;
        }
        break;
        case benefits: {
            tmp = new mAddBenifitDialog;
        }
        break;
        case specialities: {
            tmp = new mAddSpecialitiesDialog;
        }
        break;
        case document_types: {
            tmp = new mAddDocumentTypeDialog;
        }
        break;
        case specialities_sets: {
            tmp = new mAddSpecialitiesSetsDialog;
        }
        break;
        }

    QObject::connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)),
                     this, SLOT(addRow(QList<QVariant>&)));
    tmp->exec();
}

void otherTablesWindow::addRow(QList<QVariant> & vl) {

    bool f = focusWidget() != ui->otherTablesView ? true : false;

    QSqlRecord tr ((f ? ppstm : pptm)->record());
    QList<QVariant>::iterator it = vl.begin();


    if (f) {
        if (specComboBox->currentIndex() == 0) {
            tr.setValue(1, ptm->record(ui->otherTablesView->currentIndex().row())
                        .value("spec_id").toString());
            tr.setValue(0, it->toString());
        }
        else {
            tr.setValue(1, ptm->record(ui->otherTablesView->currentIndex().row())
                        .value("spec_id").toString());
            tr.setValue(tr.indexOf("entry_score"), (*(it++)).toString());
            tr.setValue(tr.indexOf("discipline_id"), (*(it++)).toString());
            tr.setValue(tr.indexOf("exam_type"), (*(it++)).toString());
        }
    }
    else
        switch (ct) {
        case disciplines: {
            tr.setGenerated(0, false);
            tr.setValue("name", it->toString());
        }
        break;
        case benefits: {
            tr.setGenerated(0, false);
            tr.setValue("benefit_name", (*(it++)).toString());
            tr.setValue("is_entry_exam", (*(it++)).toBool());
            tr.setValue("is_contest", (*(it++)).toBool());
        }
        break;
        case specialities: {
            tr.setGenerated(0, false);
            tr.setValue("name", (*(it++)).toString());
            tr.setValue("code", (*(it++)).toBool());
            tr.setValue("abbreviation", (*(it++)).toBool());
        }
        break;
        case document_types: {
            tr.setGenerated(0, false);
            tr.setValue("name", (*(it++)).toString());
            tr.setValue("is_contest", (*(it++)).toBool());
            tr.setValue("is_mandatory", (*(it++)).toBool());
        }
        break;
        case specialities_sets: {
            tr.setGenerated(0, false);
            tr.setValue("spec_id", (*(it++)).toString());
            tr.setValue("educ_form", (*(it++)).toString());
            tr.setValue("position_numbers", (*(it++)).toString());
            tr.setValue("finance_form", (*(it++)).toString());
            tr.setValue("year", (*(it++)).toString());
        }
        break;
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

void otherTablesWindow::editRowButton() {

    bool f = focusWidget() != ui->otherTablesView ? true : false;

    QDialog * tmp;

    if (f) {
        if (specComboBox->currentIndex() == 0) {
            tmp = new mSpecSetDiscAddDialog;
            ppstm->setFilter(QString("discipline_id = %1 AND spec_id = %2")
                            .arg(pstm->record(ui->otherTablesSubView->currentIndex().row())
                                 .value("discipline_id").toString())
                            .arg(pstm->record(ui->otherTablesSubView->currentIndex().row())
                                 .value("spec_id").toString()));
            ppstm->select();
            ((mSpecSetDiscAddDialog*)tmp)->fillCortege(
                        pstm->record(ui->otherTablesSubView->currentIndex().row()));
        }
        else {
            tmp = new mAddExamDialog;
            ppstm->setFilter(QString("discipline_id = %1 AND spec_id = %2")
                            .arg(pstm->record(ui->otherTablesSubView->currentIndex().row())
                                 .value("discipline_id").toString())
                            .arg(pstm->record(ui->otherTablesSubView->currentIndex().row())
                                 .value("spec_id").toString()));
            ppstm->select();
            QSqlRecord tr(pstm->record(ui->otherTablesSubView->currentIndex().row()));
            QSqlField tf(tr.field("entry_score"));
            tf.setName("score");
            tr.replace(tr.indexOf("entry_score"),tf);
            ((mAddExamDialog*)tmp)->fillCortege(
                        tr);
        }
    }
    else
    switch (ct) {
        case disciplines: {
            tmp = new mAddDisciplineDialog;
            pptm->setFilter(QString("discipline_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("discipline_id").toString()));
            pptm->select();
            ((mAddDisciplineDialog*)tmp)->fillCortege(pptm->record(0));
        }
        break;
        case benefits: {
            tmp = new mAddBenifitDialog;
            pptm->setFilter(QString("id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("id").toString()));
            pptm->select();
            ((mAddBenifitDialog*)tmp)->fillCortege(pptm->record(0));
        }
        break;
        case specialities: {
            tmp = new mAddSpecialitiesDialog;
            pptm->setFilter(QString("spec_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("spec_id").toString()));
            pptm->select();
            ((mAddSpecialitiesDialog*)tmp)->fillCortege(pptm->record(0));
        }
        break;
        case document_types: {
            tmp = new mAddDocumentTypeDialog;
            pptm->setFilter(QString("document_type_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("document_type_id").toString()));
            pptm->select();
            ((mAddDocumentTypeDialog*)tmp)->fillCortege(pptm->record(0));
        }
        break;
        case specialities_sets: {
            tmp = new mAddSpecialitiesSetsDialog;
            pptm->setFilter(QString("set_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("set_id").toString()));
            pptm->select();
            ((mAddSpecialitiesSetsDialog*)tmp)->fillCortege(
                        ptm->record(ui->otherTablesView->currentIndex().row()));
        }
        break;
        }

    QObject::connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)),
                     this, SLOT(editRow(QList<QVariant>&)));
    tmp->exec();
}

void otherTablesWindow::editRow(QList<QVariant> & vl) {

    bool f = focusWidget() != ui->otherTablesView ? true : false;

    QSqlRecord tr((f ? ppstm : pptm)->record());
    QList<QVariant>::iterator it = vl.begin();

    if (f) {
        if (specComboBox->currentIndex() == 0) {
            tr.setValue(1, pstm->record(ui->otherTablesSubView->currentIndex().row())
                        .value("spec_id").toString());
            tr.setValue(0, it->toString());
        }
        else {
            tr.setValue(1, pstm->record(ui->otherTablesSubView->currentIndex().row())
                        .value("spec_id").toString());
            tr.setValue("entry_score", (it++)->toString());
            tr.setValue("discipline_id", (it++)->toString());
            tr.setValue("exam_type", (it++)->toString());
        }
    }
    else
        switch (ct) {
        case disciplines: {
            tr.setGenerated(0, false);
            tr.setValue("name", it->toString());
        }
        break;
        case benefits: {
            tr.setGenerated(0, false);
            tr.setValue("benefit_name", (it++)->toString());
            tr.setValue("is_entry_exam", (it++)->toBool());
            tr.setValue("is_contest", (it++)->toBool());
        }
        break;
        case specialities: {
            tr.setGenerated(0, false);
            tr.setValue("name", (it++)->toString());
            tr.setValue("code", (it++)->toString());
            tr.setValue("abbreviation", (it++)->toString());
        }
        break;
        case document_types: {
            tr.setGenerated(0, false);
            tr.setValue("name", (it++)->toString());
            tr.setValue("is_contest", (it++)->toBool());
            tr.setValue("is_mandatory", (it++)->toBool());
        }
        break;
        case specialities_sets: {
            tr.setGenerated(0, false);
            tr.setValue("spec_id", (it++)->toString());
            tr.setValue("educ_form", (it++)->toString());
            tr.setValue("position_numbers", (it++)->toString());
            tr.setValue("finance_form", (it++)->toString());
            tr.setValue("year", (it++)->toString());
        }
        break;
        }

    if ((f ? ppstm : pptm)->setRecord(0, tr)) {
        QMessageBox::information(this, "Изменение строки", "Изменение строки прошло успешно");
        (f ? pstm : ptm)->select();
    }
    else {
        QMessageBox::warning(this, "Изменение строки", "Введенные данные были некорректны!");
        qDebug() << "Changing the row goes wrong!" << (f ? ppstm : pptm)->lastError().text();
        (f ? ppstm : pptm)->revertAll();
    }
}

void otherTablesWindow::deleteRowButton() {
    bool f = focusWidget() != ui->otherTablesView ? true : false;

    if (f) {
        ppstm->setFilter(QString("spec_id = %1 AND discipline_id = %2")
                        .arg(pstm->record(ui->otherTablesView->currentIndex().row())
                             .value("spec_id").toString())
                         .arg(pstm->record(ui->otherTablesView->currentIndex().row())
                              .value("discipline_id").toString()));
        ppstm->select();
    }
    else
        switch (ct) {
        case disciplines: {
            pptm->setFilter(QString("discipline_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("discipline_id").toString()));
            pptm->select();
        }
        break;
        case benefits: {
            pptm->setFilter(QString("id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("id").toString()));
            pptm->select();
        }
        break;
        case specialities: {
            pptm->setFilter(QString("spec_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("spec_id").toString()));
            pptm->select();
        }
        break;
        case document_types: {
            pptm->setFilter(QString("document_type_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("document_type_id").toString()));
            pptm->select();
        }
        break;
        case specialities_sets: {
            pptm->setFilter(QString("set_id = %1")
                            .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("set_id").toString()));
            pptm->select();
        }
        break;
        }

    if ((f ? ppstm : pptm)->removeRow(0)) {
        QMessageBox::information(this, "Удаление строки", "Удаление строки прошло успешно");
        (f ? pstm : ptm)->select();
    }
    else {
        QMessageBox::warning(this, "Удаление строки", "Удаление записи не может быть произведено!");
        qDebug() << "Deleting the row goes wrong!" << (f ? ppstm : pptm)->lastError().text();
        (f ? ppstm : pptm)->revertAll();
    }
}

void otherTablesWindow::setChanged() {//prof predmet

    pstm->setFilter(QString("spec_id = %1")
                    .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("spec_id").toInt()));
    pstm->select();
}

void otherTablesWindow::specChanged() {//obyaz exam

    pstm->setFilter(QString("spec_id = %1")
                    .arg(ptm->record(ui->otherTablesView->currentIndex().row()).value("spec_id").toInt()));
    pstm->select();
}

void otherTablesWindow::specComboBoxChanged(const int & index) {
    QObject::disconnect(ui->otherTablesView, SIGNAL(clicked(QModelIndex)),
                        this, SLOT(setChanged()));
    switch (index) {
    case 0:
        QObject::connect(ui->otherTablesView, SIGNAL(clicked(QModelIndex)),
                         this, SLOT(setChanged()));

        pstm = new QSqlRelationalTableModel(this, QSqlDatabase::database(DBName));
        ppstm = new QSqlTableModel(this, QSqlDatabase::database(DBName));

        pstm->setTable("spec_sets_disc_v");

        pstm->setFilter(QString("set_id = %1")
                        .arg(ptm->rowCount() > 0 ? 1 : -1));

        pstm->setHeaderData(2, Qt::Horizontal, "Название");
        pstm->select();

        ui->otherTablesSubView->setModel(pstm);
        ui->otherTablesSubView->setColumnHidden(0,true);
        ui->otherTablesSubView->setColumnHidden(1,true);

        ppstm->setTable("specialities_sets_disciplines");
        setChanged();

        break;
    case 1:
        QObject::connect(ui->otherTablesView, SIGNAL(clicked(QModelIndex)),
                         this, SLOT(specChanged()));
        pstm->setTable("specs_mandatory_exams_v");
        pstm->setFilter(QString("spec_id = %1")
                        .arg(ptm->record(0 ? 1 : -1).value("spec_id").toString()));
        pstm->select();

        pstm->setHeaderData(pstm->fieldIndex("entry_score"), Qt::Horizontal, "Проходной балл");
        pstm->setHeaderData(pstm->fieldIndex("exam_type"), Qt::Horizontal, "Тип экзамена");
        pstm->setHeaderData(pstm->fieldIndex("name"), Qt::Horizontal, "Дисциплина");

        ppstm->setTable("mandatory_exams");
        ppstm->select();

        ui->otherTablesSubView->setModel(pstm);
        ui->otherTablesSubView->setColumnHidden(0,true);
        ui->otherTablesSubView->setColumnHidden(1,true);

        specChanged();
        break;
    }
}

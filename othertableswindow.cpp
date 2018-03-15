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


    ptm = new QSqlTableModel(this, QSqlDatabase::database(DBName));
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

        ui->otherTablesView->setModel(ptm);
        ptm->select();

//      ui->otherTablesView->setColumnHidden(0,true);
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
        ui->otherTablesSubView->setVisible(false);

        ptm->setHeaderData(1, Qt::Horizontal, "Наименование");
        ptm->setHeaderData(2, Qt::Horizontal, "Код");
        ptm->setHeaderData(3, Qt::Horizontal, "Сокращение");
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

    QDialog * tmp;

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
    }
    QObject::connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)),
                     this, SLOT(addRow(QList<QVariant>&)));
    tmp->exec();
}

void otherTablesWindow::addRow(QList<QVariant> & vl) {

    QSqlRecord tr (pptm->record());
    QList<QVariant>::iterator it = vl.begin();

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
    }

    if (pptm->insertRecord(-1,tr)) {
        QMessageBox::information(this, "Добавление строки", "Добавление строки прошло успешно");
        ptm->select();
    }
    else {
        QMessageBox::warning(this, "Добавление строки", "Введенные данные были некорректны!");
        qDebug() << "Adding the row goes wrong!" << pptm->lastError().text();
        pptm->revertAll();
    }
}

void otherTablesWindow::editRowButton() {

    QDialog * tmp;

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
    }

    QObject::connect(tmp, SIGNAL(cortegeFormed(QList<QVariant>&)),
                     this, SLOT(editRow(QList<QVariant>&)));
    tmp->exec();
}

void otherTablesWindow::editRow(QList<QVariant> & vl) {

    QSqlRecord tr(pptm->record());
    QList<QVariant>::iterator it = vl.begin();

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
    }

    if (pptm->setRecord(0, tr)) {
        QMessageBox::information(this, "Изменение строки", "Изменение строки прошло успешно");
        ptm->select();
    }
    else {
        QMessageBox::warning(this, "Изменение строки", "Введенные данные были некорректны!");
        qDebug() << "Changing the row goes wrong!" << pptm->lastError().text();
        pptm->revertAll();
    }
}

void otherTablesWindow::deleteRowButton() {

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
    }

    if (pptm->removeRow(0)) {
        QMessageBox::information(this, "Удаление строки", "Удаление строки прошло успешно");
        ptm->select();
    }
    else {
        QMessageBox::warning(this, "Удаление строки", "Удаление записи не может быть произведено!");
        qDebug() << "Deleting the row goes wrong!" << pptm->lastError().text();
        pptm->revertAll();
    }
}

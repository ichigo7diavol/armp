#include "maddspecialitiessetsdialog.h"
#include "ui_maddspecialitiessetsdialog.h"

mAddSpecialitiesSetsDialog::mAddSpecialitiesSetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddSpecialitiesSetsDialog)
{

    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Контрольные цифры");

    setAttribute(Qt::WA_DeleteOnClose);

    pstm = new QSqlTableModel(this, QSqlDatabase::database(DBName));
    pstm->setTable("specialities");
    pstm->select();

    ui->specComboBox->setModel(pstm);
    ui->specComboBox->setModelColumn(1);

    pftm = new QSqlTableModel(this, QSqlDatabase::database(DBName));
    pftm->setTable("finance_form_v");
    pftm->select();

    ui->financeFormComboBox->setModel(pftm);
    ui->financeFormComboBox->setModelColumn(0);

    petm = new QSqlTableModel(this, QSqlDatabase::database(DBName));
    petm->setTable("educ_form_v");
    petm->select();

    ui->educFormComboBox->setModel(petm);
    ui->educFormComboBox->setModelColumn(0);

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

void mAddSpecialitiesSetsDialog::formCortege() {
    QList <QVariant> tmp;
    tmp << pstm->record(ui->specComboBox->currentIndex()).value("spec_id")
        << ui->educFormComboBox->currentText()
        << ui->countLineEdit->text()
        << ui->financeFormComboBox->currentText()
        << ui->yearLineEdit->text();

    setVisible(false);
    emit cortegeFormed(tmp);
    close();
}


void mAddSpecialitiesSetsDialog::fillCortege(const QSqlRecord & rec) {
    ui->specComboBox->setCurrentText(rec.value(1).toString());
    ui->educFormComboBox->setCurrentText(rec.value("educ_form").toString());
    ui->countLineEdit->setText(rec.value("position_numbers").toString());
    ui->financeFormComboBox->setCurrentText(rec.value("finance_form").toString());
    ui->yearLineEdit->setText(rec.value("year").toString());
}

mAddSpecialitiesSetsDialog::~mAddSpecialitiesSetsDialog()
{
    delete ui;
}

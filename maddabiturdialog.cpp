#include "maddabiturdialog.h"
#include "ui_maddabiturdialog.h"

mAddAbiturDialog::mAddAbiturDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddAbiturDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    pelcbm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pelcbm->setTable("education_level_view");
    pelcbm->select();

    ui->eduLvlComboBox->setModel(pelcbm);
    ui->eduLvlComboBox->setModelColumn(0);

    pbcbm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pbcbm->setTable("benefits");
    pbcbm->select();

    ui->privilegeComboBox->setModel(pbcbm);
    ui->privilegeComboBox->setModelColumn(1);
    qDebug() << ui->privilegeComboBox->currentIndex();

    ui->genderComboBox->addItem(QString("мужской"));
    ui->genderComboBox->addItem(QString("женский"));

    setAttribute(Qt::WA_DeleteOnClose);

    this->connect(ui->cancelPushButton, SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton, SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddAbiturDialog::~mAddAbiturDialog() {

    qDebug() << this->objectName() + QString(" deleted!");
    delete ui;
}

void mAddAbiturDialog::formCortege() {

    QList <QVariant> vl;

    vl << ui->secNameLineEdit->text() << QVariant(ui->nameLineEdit->text())
       << ui->midNameLineEdit->text()
       << ui->secNameLineEdit->text() << QVariant(ui->regDateEdit->date())
       << ui->exumNumLineEdit->text().toInt()
       << ui->enlistedCheckBox->isChecked() << ui->privilegeComboBox->currentIndex() + 1
       << ui->birthDateEdit->date()
       << ui->genderComboBox->currentText() << ui->citizenshipLineEdit->text()
       << ui->phoneLineEdit->text()
       << ui->eduLvlComboBox->currentText() << ui->endYearSpinBox->value()
       << ui->avgScoreLineEdit->text().toFloat() << ui->dormitoryCheckBox->isChecked()
       << ui->noteTextEdit->toPlainText()
       << ui->nationLineEdit->text() << ui->mailLineEdit->text();


    emit this->cortegeFormed(vl);
}

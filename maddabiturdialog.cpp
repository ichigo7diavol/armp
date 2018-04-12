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

    setWindowTitle("Абитуриент");

    pelcbm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pelcbm->setTable("educ_lvl_v");
    pelcbm->select();

    ui->eduLvlComboBox->setModel(pelcbm);
    ui->eduLvlComboBox->setModelColumn(0);

    pgcbm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pgcbm->setTable("gender_v");
    pgcbm->select();

    ui->genderComboBox->setModel(pgcbm);
    ui->genderComboBox->setModelColumn(0);

    pbcbm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pbcbm->setTable("benefits");
    pbcbm->select();

    ui->privilegeComboBox->setModel(pbcbm);
    ui->privilegeComboBox->setModelColumn(1);

    setAttribute(Qt::WA_DeleteOnClose);

    this->connect(ui->cancelPushButton, SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton, SIGNAL(clicked(bool)), SLOT(formCortege()));

    ui->benLabel->setVisible(false);
    ui->privilegeComboBox->setVisible(false);

    ui->avgLabel->setVisible(false);
    ui->avgScoreLineEdit->setVisible(false);
}

mAddAbiturDialog::~mAddAbiturDialog() {

    qDebug() << this->objectName() + QString(" deleted!");
    delete ui;
}

void mAddAbiturDialog::formCortege() {

    // reg_num, reg_date, sec_name, name, mid_name, birth_date, citizenship, phone_number, email,
    // avg_score, benefit_id, is_dormitory, is_enlisted, gender, educ_lvl (нескрытые стобцы)

    // reg_adr, live_adr, end_educ_year, is_rules_agreed, is_date_agreed, is_first_spo, is_data_proc_agreed,
    // note (скрытые столбцы)

    // set_id (добавляются через другие формы)

    QList <QVariant> vl;

    /*<< ui->regLineEdit->text().toInt()*/

    vl << ui->regDateEdit->date()
       << ui->secNameLineEdit->text() << ui->nameLineEdit->text()
       << ui->midNameLineEdit->text() << ui->birthDateEdit->text()
       << ui->citizenshipLineEdit->text() << ui->phoneLineEdit->text()
       << ui->mailLineEdit->text()
       //<< ui->avgScoreLineEdit->text().toFloat()
       << pbcbm->record(ui->privilegeComboBox->currentIndex()).value("id")
       << ui->dormitoryCheckBox->isChecked()
       << ui->enlistedCheckBox->isChecked() << ui->genderComboBox->currentText()
       << ui->eduLvlComboBox->currentText()

       << ui->regAdrTextEdit->toPlainText() << ui->liveAdrTextEdit->toPlainText()
       << ui->endYearSpinBox->value() << ui->rulesAgreeCheckBox->isChecked()
       << ui->dateAgreeCheckBox->isChecked() << ui->firstSPOCheckBox->isChecked()
       << ui->procAgreeCheckBox->isChecked() << ui->noteTextEdit->toPlainText();

    setVisible(false);
    emit cortegeFormed(vl);
    close();
}

void mAddAbiturDialog::fillCortege(const QSqlRecord && cor, QVector<int> & sci) {

  char i = 0;

  //ui->regLineEdit->setText(cor.value(0).toString());
  ui->regDateEdit->setDate(cor.value("reg_date").toDate());
  ui->secNameLineEdit->setText(cor.value("sec_name").toString());
  ui->nameLineEdit->setText(cor.value("name").toString());
  ui->midNameLineEdit->setText(cor.value("mid_name").toString());
  ui->birthDateEdit->setDate(cor.value("birth_date").toDate());
  ui->citizenshipLineEdit->setText(cor.value("citizenship").toString());
  ui->phoneLineEdit->setText(cor.value("phone_number").toString());
  ui->mailLineEdit->setText(cor.value("email").toString());
  i++;
  //ui->avgScoreLineEdit->setText(cor.value(sci[i++]).toString());

  //ui->privilegeComboBox->setCurrentText(cor.value("sec_name").toString());

  ui->dormitoryCheckBox->setChecked(cor.value("is_dormitory").toBool());
  ui->enlistedCheckBox->setChecked(cor.value("is_courses").toBool());
  ui->genderComboBox->setCurrentText(cor.value("gender").toString());
  ui->eduLvlComboBox->setCurrentText(cor.value("educ_lvl").toString());
  ui->regAdrTextEdit->setText(cor.value("reg_adr").toString());
  ui->liveAdrTextEdit->setText(cor.value("live_adr").toString());
  ui->endYearSpinBox->setValue(cor.value("end_educ_year").toInt());
  ui->rulesAgreeCheckBox->setChecked(cor.value("is_rules").toBool());
  ui->dateAgreeCheckBox->setChecked(cor.value("is_date").toBool());
  ui->firstSPOCheckBox->setChecked(cor.value("is_first_spo").toBool());
  ui->procAgreeCheckBox->setChecked(cor.value("is_proc").toBool());
  ui->noteTextEdit->setText(cor.value("note").toString());
}

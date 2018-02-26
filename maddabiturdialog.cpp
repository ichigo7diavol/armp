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

    QSqlRecord record;
    QSqlField tmp;

    tmp.setGenerated(false);

    tmp.setValue(QVariant(10));
    tmp.setName(QString("reg_number"));
    record.append(tmp);
    /*
    tmp.setValue(QVariant(ui->exumNumLineEdit->text()));
    tmp.setName(QString("sec_name"));
    record.append(tmp);

    qDebug() << record;

    tmp.setValue(QVariant(ui->secNameLineEdit->text()));
    tmp.setName(QString("name"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->midNameLineEdit->text()));
    tmp.setName(QString("mid_name"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->birthDateEdit->date()));
    tmp.setName(QString("birth_date"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->regDateEdit->date()));
    tmp.setName(QString("reg_date"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->exumNumLineEdit->text().toInt()));
    tmp.setName(QString("num_ex_list"));
    record.append(tmp);


    //tmp.setValue(QVariant(ui->birthPlaceLineEdit->text()));
    //tmp.setName(QString("birth_place"));
    //record.append(tmp);

    tmp.setValue(QVariant(ui->genderComboBox->currentText()));
    tmp.setName(QString("gender"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->citizenshipLineEdit->text()));
    tmp.setName(QString("citizenship"));
    record.append(tmp);

    //tmp.setValue(QVariant(ui->regAdrTextEdit->toPlainText()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->liveAdrTextEdit->toPlainText()));
    //record.append(tmp);

    tmp.setValue(QVariant(ui->phoneLineEdit->text()));
    tmp.setName(QString("phone"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->mailLineEdit->text()));
    tmp.setName(QString("email"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->eduLvlComboBox->currentText()));
    tmp.setName(QString("educ_lvl"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->endYearSpinBox->value()));
    tmp.setName(QString("educ_end_year"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->avgScoreLineEdit->text().toFloat()));
    tmp.setName(QString("avg_score"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->privilegeComboBox->currentIndex() + 1));
    tmp.setName(QString("benefits"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->nationLineEdit->text()));
    tmp.setName(QString("nation"));
    record.append(tmp);

    //tmp.setValue(QVariant(ui->targeRecCheckBox->isChecked()));
    //tmp.setName(QString(""));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->workPlaceLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->workPosLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->seniorityYearLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->seniorityMonthLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->motherFIOLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->motherWorkLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->motherPhoneLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->fatherFIOLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->fatherWorkLineEdit->text()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->fatherPhoneLineEdit->text()));
    //record.append(tmp);

    tmp.setValue(QVariant(ui->dormitoryCheckBox->isChecked()));
    tmp.setName(QString("dormitory"));
    record.append(tmp);

    //tmp.setValue(QVariant(ui->rulesAgreeCheckBox->isChecked()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->dateAgreeCheckBox->isChecked()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->firstSPOCheckBox->isChecked()));
    //record.append(tmp);

    //tmp.setValue(QVariant(ui->procAgreeCheckBox->isChecked()));
    //record.append(tmp);

    tmp.setValue(QVariant(ui->noteTextEdit->toPlainText()));
    tmp.setName(QString("note"));
    record.append(tmp);

    tmp.setValue(QVariant(ui->enlistedCheckBox->isChecked()));
    tmp.setName(QString("enlisted"));
    record.append(tmp);
    */
    emit this->cortegeFormed(record);
}

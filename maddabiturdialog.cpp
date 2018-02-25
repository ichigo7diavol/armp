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

    ui->genderComboBox->addItem(QString("мужской"));
    ui->genderComboBox->addItem(QString("женский"));

    setAttribute(Qt::WA_DeleteOnClose);

    this->connect(ui->cancelPushButton, SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->cancelPushButton, SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddAbiturDialog::~mAddAbiturDialog() {
    delete ui;
}

void mAddAbiturDialog::formCortege() {

    QSqlRecord record;

}

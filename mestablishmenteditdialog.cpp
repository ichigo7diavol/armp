#include "mestablishmenteditdialog.h"
#include "ui_mestablishmenteditdialog.h"

mEstablishmentEditDialog::mEstablishmentEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mEstablishmentEditDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Учреждение");

    //setAttribute(Qt::WA_DeleteOnClose);

    etm = new QSqlTableModel(this, QSqlDatabase::database(DBName));
    etm->setTable("establishment_info");
    etm->select();

    QSqlRecord tmpRec = etm->record(0);

    ui->estNameLineEdit->setText(tmpRec.value("est_name").toString());
    ui->yearLineEdit->setText(tmpRec.value("current_year").toString());
    ui->estLvlLineEdit->setText(tmpRec.value("est_lvl").toString());
    ui->collegeNameLineEdit->setText(tmpRec.value("college_name").toString());
    ui->rectorLineEdit->setText(tmpRec.value("rector").toString());
    ui->priemSecrLineEdit->setText(tmpRec.value("otv_sec_priem").toString());
    ui->firstRecLineEdit->setText(tmpRec.value("first_prorec").toString());
    ui->principalaLineEdit->setText(tmpRec.value("principal").toString());

    QObject::connect(ui->okPushButton, SIGNAL(clicked(bool)),
                     this, SLOT(close()));
    QObject::connect(ui->cancelPushButton, SIGNAL(clicked(bool)),
                     this, SLOT(close()));
}

mEstablishmentEditDialog::~mEstablishmentEditDialog()
{
    delete ui;
}

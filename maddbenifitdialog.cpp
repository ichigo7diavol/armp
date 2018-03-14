#include "maddbenifitdialog.h"
#include "ui_maddbenifitdialog.h"

mAddBenifitDialog::mAddBenifitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddBenifitDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Льгота");

    setAttribute(Qt::WA_DeleteOnClose);

//    ntm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
//    ntm->setTable("benefits");
//    ntm->select();

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddBenifitDialog::~mAddBenifitDialog()
{
    delete ui;
}

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

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddBenifitDialog::~mAddBenifitDialog()
{
    delete ui;
}

void mAddBenifitDialog::formCortege() {

    QList <QVariant> vl;

    vl << ui->nameLineEdit->text()
       << ui->entryCheckBox->isChecked()
       << ui->contesstCheckBox->isChecked();

    setVisible(false);
    emit cortegeFormed(vl);
    close();
}


void mAddBenifitDialog::fillCortege(const QSqlRecord & rec) {

    ui->nameLineEdit->setText(rec.value("benefit_name").toString());
    ui->entryCheckBox->setChecked(rec.value("is_entry_exam").toBool());
    ui->contesstCheckBox->setChecked(rec.value("is_contest").toBool());
}

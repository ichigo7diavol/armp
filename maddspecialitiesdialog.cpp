#include "maddspecialitiesdialog.h"
#include "ui_maddspecialitiesdialog.h"

mAddSpecialitiesDialog::mAddSpecialitiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddSpecialitiesDialog)
{

    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Специальность");

    setAttribute(Qt::WA_DeleteOnClose);

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

void mAddSpecialitiesDialog::formCortege() {
    QList <QVariant> tmp;
    tmp << ui->nameLineEdit->text() << ui->codeLineEdit->text()
        << ui->abrvLineEdit->text();

    setVisible(false);
    emit cortegeFormed(tmp);
    close();
}


void mAddSpecialitiesDialog::fillCortege(const QSqlRecord & rec) {
    ui->nameLineEdit->setText(rec.value(1).toString());
    ui->codeLineEdit->setText(rec.value(2).toString());
    ui->abrvLineEdit->setText(rec.value(3).toString());
}

mAddSpecialitiesDialog::~mAddSpecialitiesDialog()
{
    delete ui;
}

#include "madddocumenttypedialog.h"
#include "ui_madddocumenttypedialog.h"

mAddDocumentTypeDialog::mAddDocumentTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddDocumentTypeDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Тип документа");

    setAttribute(Qt::WA_DeleteOnClose);

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

void mAddDocumentTypeDialog::formCortege() {
    QList <QVariant> tmp;
    tmp << ui->nameLineEdit->text() << ui->contestCheckBox->isChecked()
        << ui->mandatoryCheckBox->isChecked();

    setVisible(false);
    emit cortegeFormed(tmp);
    close();
}


void mAddDocumentTypeDialog::fillCortege(const QSqlRecord & rec) {
    ui->nameLineEdit->setText(rec.value(1).toString());
    ui->contestCheckBox->setChecked(rec.value("is_contest").toBool());
    ui->mandatoryCheckBox->setChecked(rec.value("is_mandatory").toBool());
}


mAddDocumentTypeDialog::~mAddDocumentTypeDialog()
{
    delete ui;
}

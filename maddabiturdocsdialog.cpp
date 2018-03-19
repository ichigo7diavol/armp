#include "maddabiturdocsdialog.h"
#include "ui_maddabiturdocsdialog.h"

mAddAbiturDocsDialog::mAddAbiturDocsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddAbiturDocsDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Документ");

    setAttribute(Qt::WA_DeleteOnClose);

    ntm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    ntm->setTable("document_types");
    ntm->select();

    ui->docNameComboBox->setModel(ntm);
    ui->docNameComboBox->setModelColumn(1);


    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddAbiturDocsDialog::~mAddAbiturDocsDialog()
{
    delete ui;
}

void mAddAbiturDocsDialog::formCortege() {
    QList<QVariant> vl;

    vl << ntm->record(ui->docNameComboBox->currentIndex()).value("document_type_id")
       << ui->docNumLineEdit->text()
       << ui->docSeriesLineEdit->text()
       << ui->receiveDateEdit->date()
       << ui->receivedFromTextEdit->toPlainText()
       << ui->docCountLineEdit->text()
       << ui->copyCheckBox->isChecked()
       << ui->issuedCheckBox->isChecked();

    setVisible(false);
    emit cortegeFormed(vl);
    close();
}

void mAddAbiturDocsDialog::fillCortege(const QSqlRecord & rec) {
    ui->docNameComboBox->setCurrentText(rec.value("name").toString());
    ui->docNumLineEdit->setText(rec.value("number").toString());
    ui->docSeriesLineEdit->setText(rec.value("series").toString());
    ui->receiveDateEdit->setDate(rec.value("date").toDate());
    ui->receivedFromTextEdit->setText(rec.value("issued_by").toString());
    ui->docCountLineEdit->setText(rec.value("count").toString());
    ui->copyCheckBox->setChecked(rec.value("is_copy").toBool());
    ui->issuedCheckBox->setChecked(rec.value("is_issued").toBool());
}

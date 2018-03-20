#include "maddabiturmarkdialog.h"
#include "ui_maddabiturmarkdialog.h"

mAddAbiturMarkDialog::mAddAbiturMarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddAbiturMarkDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Оценка аттестата за дисциплину");

    setAttribute(Qt::WA_DeleteOnClose);

    ptm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    ptm->setTable("disciplines");
    ptm->select();

    ui->discComboBox->setModel(ptm);
    ui->discComboBox->setModelColumn(ptm->fieldIndex("name"));

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddAbiturMarkDialog::~mAddAbiturMarkDialog()
{
    delete ui;
}

void mAddAbiturMarkDialog::formCortege() {

    QList <QVariant> vl;

    vl << ptm->record(ui->discComboBox->currentIndex()).value("discipline_id")
       << ui->markLineEdit->text();

    setVisible(false);
    emit cortegeFormed(vl);
    close();
}


void mAddAbiturMarkDialog::fillCortege(const QSqlRecord & rec) {

    ui->discComboBox->setCurrentText(rec.value("name").toString());
    ui->markLineEdit->setText(rec.value("mark").toString());
}

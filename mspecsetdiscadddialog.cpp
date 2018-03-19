#include "mspecsetdiscadddialog.h"
#include "ui_mspecsetdiscadddialog.h"

mSpecSetDiscAddDialog::mSpecSetDiscAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mSpecSetDiscAddDialog)
{

    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Дисциплина");

    setAttribute(Qt::WA_DeleteOnClose);

    ptm = new QSqlTableModel(this, QSqlDatabase::database(DBName));
    ptm->setTable("disciplines");
    ptm->select();

    ui->discComboBox->setModel(ptm);
    ui->discComboBox->setModelColumn(1);

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

void mSpecSetDiscAddDialog::formCortege() {
    QList <QVariant> tmp;

    tmp << ptm->record(ui->discComboBox->currentIndex()).value("discipline_id");

    setVisible(false);
    emit cortegeFormed(tmp);
    close();
}


void mSpecSetDiscAddDialog::fillCortege(const QSqlRecord & rec) {

    ui->discComboBox->setCurrentText(rec.value("name").toString());
}

mSpecSetDiscAddDialog::~mSpecSetDiscAddDialog()
{
    delete ui;
}

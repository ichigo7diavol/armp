#include "maddspecdialog.h"
#include "ui_maddspecdialog.h"

mAddSpecDialog::mAddSpecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddSpecDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Специальность");

    pstm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pstm->setTable("specialities");
    pstm->select();

    ui->specComboBox->setModel(pstm);
    ui->specComboBox->setModelColumn(1);

    petm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    petm->setTable("educ_form_v");
    petm->select();

    ui->educFormComboBox->setModel(petm);
    ui->educFormComboBox->setModelColumn(0);

    pftm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    pftm->setTable("finance_form_v");
    pftm->select();

    ui->financeFormComboBox->setModel(pftm);
    ui->financeFormComboBox->setModelColumn(0);

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    QObject::connect(ui->okPushButton, SIGNAL(clicked(bool)),
                     this, SLOT(formCortege()));
}

void mAddSpecDialog::formCortege() {
    QList <QVariant> tmp;
    tmp << pstm->record(ui->specComboBox->currentIndex()).value("spec_id").toInt()
        << ui->educFormComboBox->currentText()
        << ui->financeFormComboBox->currentText()
        << ui->prioritySpinBox->value();

    qDebug() << tmp;
    setVisible(false);
    emit cortegeFormed(tmp);
    close();
}


void mAddSpecDialog::fillCortege(const QSqlRecord & rec) {
    ui->specComboBox->setCurrentText(rec.value(2).toString());
    ui->educFormComboBox->setCurrentText(rec.value(4).toString());
    ui->financeFormComboBox->setCurrentText(rec.value(5).toString());
    ui->prioritySpinBox->setValue(rec.value("priority").toInt());
}

mAddSpecDialog::~mAddSpecDialog()
{
    delete ui;
}

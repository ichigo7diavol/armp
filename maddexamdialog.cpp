#include "maddexamdialog.h"
#include "ui_maddexamdialog.h"

mAddExamDialog::mAddExamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddExamDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Экзамен");

    setAttribute(Qt::WA_DeleteOnClose);

    ttm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    ttm->setTable("exam_types_v");
    ttm->select();

    ui->typeComboBox->setModel(ttm);
    ui->typeComboBox->setModelColumn(0);

    dtm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    dtm->setTable("disciplines");
    dtm->select();

    ui->disciplineComboBox->setModel(dtm);
    ui->disciplineComboBox->setModelColumn(1);

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddExamDialog::~mAddExamDialog()
{
    delete ui;
}

void mAddExamDialog::formCortege(){
    QList<QVariant> vl;

    vl << ui->markLineEdit->text()
       << dtm->record(ui->disciplineComboBox->currentIndex())
          .value("discipline_id")
       << ui->typeComboBox->currentText();

    setVisible(false);
    emit cortegeFormed(vl);
    close();
}

void mAddExamDialog::fillCortege(const QSqlRecord & rec) {

    ui->markLineEdit->setText(rec.value("score").toString());
    ui->typeComboBox->setCurrentText(rec.value("exam_type").toString());
    ui->disciplineComboBox->setCurrentText(rec.value("name").toString());
}

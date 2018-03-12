#include "madddisciplinedialog.h"
#include "ui_madddisciplinedialog.h"

mAddDisciplineDialog::mAddDisciplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddDisciplineDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Дисциплина");

    setAttribute(Qt::WA_DeleteOnClose);

    this->connect(ui->cancelPushButton, SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton, SIGNAL(clicked(bool)), SLOT(formCortege()));
}

mAddDisciplineDialog::~mAddDisciplineDialog()
{
    qDebug() << "mAddDisciplineDialog deleted";

    delete ui;
}

void mAddDisciplineDialog::formCortege() {
    QList<QVariant> vl;

    vl << ui->lineEdit->text();

    setVisible(false);
    emit cortegeFormed(vl);
    close();
}

void mAddDisciplineDialog::fillCortege(const QSqlRecord & rec) {
    ui->lineEdit->setText(rec.value("name").toString());
}

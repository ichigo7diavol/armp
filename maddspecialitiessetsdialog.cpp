#include "maddspecialitiessetsdialog.h"
#include "ui_maddspecialitiessetsdialog.h"

mAddSpecialitiesSetsDialog::mAddSpecialitiesSetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mAddSpecialitiesSetsDialog)
{
    ui->setupUi(this);

    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    setWindowTitle("Контрольные цифры");

    setAttribute(Qt::WA_DeleteOnClose);

    ptm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    ptm->setTable("specialities_sets");
    ptm->select();



    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));

}

mAddSpecialitiesSetsDialog::~mAddSpecialitiesSetsDialog()
{
    delete ui;
}

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
}

mAddAbiturDocsDialog::~mAddAbiturDocsDialog()
{
    delete ui;
}

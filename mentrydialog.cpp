#include "mentrydialog.h"
#include "ui_mentrydialog.h"

mEntryDialog::mEntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mEntryDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags(this->windowFlags());

    setWindowFlags(flags ^ Qt::WindowContextHelpButtonHint
                   | Qt::MSWindowsFixedSizeDialogHint
                   );

    QObject::connect(ui->ConnectButton,QPushButton::clicked,
                     this, mEntryDialog::dbConnect);

    setAttribute(Qt::WA_DeleteOnClose);
}

void mEntryDialog::dbConnect ()
{
    QSqlDatabase db = QSqlDatabase::database(DBName);

    if (!db.isValid()) {

        db = QSqlDatabase::addDatabase("QPSQL", DBName);

        if (!db.isValid()) {

            QMessageBox::critical(this, "Ошибка", DBCreationError);
            exit(1);
        }

#ifdef ARM_DEBUG
        db.setHostName(DefIpHost);
        db.setDatabaseName(DefDBName);
        db.setUserName(DefUserName);
        db.setPassword(DefPassword);
        db.setPort(DefPort);
#else
        db.setHostName(ui->HostEdit->text());
        db.setDatabaseName(ui->BDNameEdit->text());
        db.setUserName(ui->UserNameEdit->text());
        db.setPassword(ui->PasswordEdit->text());
        db.setPort(ui->PortEdit->text().toInt());
#endif

    }

    if (!db.open()) {

        QMessageBox::warning(this, "Ошибка", QString(ConnectionError));
    }
    else {

        emit dbConnected();
        close();
    }
}

mEntryDialog::~mEntryDialog()
{
    delete ui;
}

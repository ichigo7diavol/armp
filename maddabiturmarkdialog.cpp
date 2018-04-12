#include "maddabiturmarkdialog.h"
#include "ui_maddabiturmarkdialog.h"

mAddAbiturMarkDialog::mAddAbiturMarkDialog(QWidget *parent, int nri) :
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

    ri = nri;

    ptm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    ptm->setTable("disciplines");
    ptm->select();

    pamtm = new QSqlTableModel (this, QSqlDatabase::database(QString(DBName)));
    pamtm->setTable("education_certificates");
    pamtm->select();

    cp = 1;

    labv << ui->label_1 << ui->label_2
         << ui->label_3 << ui->label_4
         << ui->label_5;

    linev << ui->markLineEdit_1 << ui->markLineEdit_2
          << ui->markLineEdit_3 << ui->markLineEdit_4
          << ui->markLineEdit_5;

    for(auto x : linev) {
        x->setValidator(new QRegExpValidator(QRegExp("[345]"), this));
        QObject::connect(x, SIGNAL(textChanged(const QString&)),
                         this, SLOT(textChanged(const QString&)));
    }

    for (int i = 0; i < ptm->rowCount(); ++i)
        if (!map.contains(ptm->record(i).value("discipline_id").toInt())) {
            pamtm->setFilter(QString("reg_num = %1 AND discipline_id = %2").arg(QString::number(ri)).arg(ptm->record((cp - 1) * 5 + i).value("discipline_id").toInt()));
            pamtm->select();

            if (pamtm->rowCount() > 0) {
                map[ptm->record(i).value("discipline_id").toInt()] = pamtm->record(0).value("mark").toInt();
            }
        }

    visualize();

    ui->backPushButton->setEnabled(false);

    if (ptm->rowCount() < 5) {
        ui->nextPushButton->setEnabled(false);
    }

    //ui->discComboBox->setModel(ptm);
    //ui->discComboBox->setModelColumn(ptm->fieldIndex("name"));

    this->connect(ui->cancelPushButton,
                  SIGNAL(clicked(bool)), SLOT(reject()));
    this->connect(ui->okPushButton,
                  SIGNAL(clicked(bool)), SLOT(formCortege()));
    this->connect(ui->nextPushButton,
                  SIGNAL(clicked(bool)), SLOT(nextPage()));
    this->connect(ui->backPushButton,
                  SIGNAL(clicked(bool)), SLOT(prevPage()));
}

void mAddAbiturMarkDialog::textChanged(const QString & newText) {
    if (newText.isEmpty())
        return;

    int index = QObject::sender()->objectName().at(QObject::sender()->objectName().length() - 1).digitValue() - 1;
    map[ptm->record((cp - 1) * 5 + index).value("discipline_id").toInt()] = newText.toInt();
}

void mAddAbiturMarkDialog::visualize() {

    if (ptm->rowCount() == 0)
        return;

    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);

    ui->markLineEdit_1->setVisible(false);
    ui->markLineEdit_2->setVisible(false);
    ui->markLineEdit_3->setVisible(false);
    ui->markLineEdit_4->setVisible(false);
    ui->markLineEdit_5->setVisible(false);

    ui->markLineEdit_1->setText("");
    ui->markLineEdit_2->setText("");
    ui->markLineEdit_3->setText("");
    ui->markLineEdit_4->setText("");
    ui->markLineEdit_5->setText("");

    qDebug() << ptm->rowCount() % 5;

    for (int i = 0; (i < 5) && (i < ptm->rowCount() - (cp - 1) * 5); ++i) {
        labv[i]->setVisible(true);
        labv[i]->setText(ptm->record((cp - 1) * 5 + i).value("name").toString() + (ptm->record((cp - 1) * 5 + i).value("is_cert").toBool() ? "*" : ""));

        linev[i]->setVisible(true);

        if (map.contains(ptm->record((cp - 1) * 5 + i).value("discipline_id").toInt())) {
            qDebug() << ptm->record((cp - 1) * 5 + i).value("discipline_id").toInt();
            linev[i]->setText(QString::number(map[ptm->record((cp - 1) * 5 + i).value("discipline_id").toInt()]));
        }
    }


}

void mAddAbiturMarkDialog::nextPage() {
    if (cp == 1)
        ui->backPushButton->setEnabled(true);
    ++cp;

    if (ptm->rowCount() < cp * 5)
        ui->nextPushButton->setEnabled(false);

    visualize();
}

void mAddAbiturMarkDialog::prevPage() {
    if (cp == 2)
        ui->backPushButton->setEnabled(false);
    --cp;

    ui->nextPushButton->setEnabled(true);

    visualize();
}


mAddAbiturMarkDialog::~mAddAbiturMarkDialog()
{
    delete ui;
}

void mAddAbiturMarkDialog::formCortege() {

    //QList <QVariant> vl;

    //vl << ptm->record(ui->discComboBox->currentIndex()).value("discipline_id")
    //   << ui->markLineEdit->text();

    QString poolMarks;
    QString poolDisc;

    for(auto x : map.keys()) {
        poolMarks += (poolMarks.isEmpty() ? QString("") : QString(",")) + QString::number(map.value(x));
        poolDisc += (poolDisc.isEmpty() ? QString("") : QString(",")) + QString::number(x);
    }

    QSqlQuery query(QSqlDatabase::database(DBName));

    query.exec(QString("select delete_cert_marks(%1)").arg(QString::number(ri)));
    //qDebug() << query.lastQuery();

    query.exec(QString("select add_cert_marks('{%1}', '{%2}', %3)").arg(poolDisc).arg(poolMarks).arg(QString::number(ri)));
    //qDebug() << QString("select add_cert_marks('{%1}', '{%2}', %3)").arg(poolDisc).arg(poolMarks).arg(QString::number(ri));

    setVisible(false);
    //emit cortegeFormed(vl);
    close();
}


void mAddAbiturMarkDialog::fillCortege(const int nri) {
    //ri = nri;
    //qDebug() << ri;
    //ui->discComboBox->setCurrentText(rec.value("name").toString());
    //ui->markLineEdit->setText(rec.value("mark").toString());
}

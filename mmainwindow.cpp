#include "mmainwindow.h"
#include "ui_mmainwindow.h"


mMainWindow::mMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mMainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("АРМ Приемная комиссия"));

    QMenu * pm;
    QList <QAction*> lpa; // list ptr action
    QAction * pa; // ptr action

    // ПУНКТ ФАЙЛ

    pm = ui->menuBar->addMenu("Файл");

    pa = new QAction("Выход");
    this->connect(pa, SIGNAL(triggered()), SLOT(close()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    ui->statusBar->setVisible(false);
    ui->mainToolBar->setVisible(false);

    // ПУНКТ СПРАВОЧНИКИ

    pm = ui->menuBar->addMenu("Справочники");
    pa = new QAction("Абитуриенты");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openAbiturientsTable()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();
    pm->addSeparator();

    pa = new QAction("Учреждение");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openEstablishmentDialog()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();
    pm->addSeparator();

    pa = new QAction("Дисциплины");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openDisciplineTable()));
    lpa << pa;

    pa = new QAction("Специальности");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openSpecialitiesTable()));
    lpa << pa;

    pa = new QAction("Контрольные цифры приема");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openSpecialitiesSetsTable()));
    lpa << pa;

    pa = new QAction("Типы документов");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(openDocumentTypesTable()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ ДОКУМЕНТЫ

    pm = ui->menuBar->addMenu("Документы");

    pa = new QAction("Произвести ранжирование");
    this->connect(pa, SIGNAL(triggered(bool)), SLOT(startRange()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();

    // ПУНКТ СЕРВИС

    // ПУНКТ ОКНО

    pm = ui->menuBar->addMenu("Окно");
    pa = new QAction("Расположить каскадом");
    ui->mdiArea->connect(pa, SIGNAL(triggered(bool)), SLOT(cascadeSubWindows()));
    lpa << pa;

    pa = new QAction("Расположить мазайкой");
    ui->mdiArea->connect(pa, SIGNAL(triggered(bool)), SLOT(tileSubWindows()));
    lpa << pa;

    pm->addActions(lpa);
    lpa.clear();
}

void mMainWindow::openEstablishmentDialog() {

    mEstablishmentEditDialog tmp;
    tmp.exec();

}

mMainWindow::~mMainWindow()
{
    delete ui;
}

void mMainWindow::openAbiturientsTable() {

    if (!findChild<mAbiturTableWindow*>(QString("mAbiturTableWindow"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new mAbiturTableWindow());

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Абитуриенты"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "mAbiturTableWindow is already opened!";
    }
}

void mMainWindow::openDisciplineTable() {

    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowDisciplines"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::disciplines));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Дисциплины"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "otherTablesWindow[Disciplines] is already opened!";
    }
}

void mMainWindow::openBenefitsTable() {
    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowBenefits"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::benefits));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Льготы"));

        tmp->show();

//        qDebug() << "mAbiturTableWindow created!";
    }
    else {
        qDebug() << "otherTablesWindow[Benefits] is already opened!";
    }
}

void mMainWindow::openSpecialitiesTable() {
    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowSpecialities"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::specialities));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Специальности"));

        tmp->show();
    }
    else {
        qDebug() << "otherTablesWindow[Specialities] is already opened!";
    }
}

void mMainWindow::openSpecialitiesSetsTable() {
    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowSpecialitiesSets"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::specialities_sets));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Контрольные цифры"));

        tmp->show();
    }
    else {
        qDebug() << "otherTablesWindow[SpecialitiesSets] is already opened!";
    }
}

void mMainWindow::openDocumentTypesTable() {
    if (!findChild<otherTablesWindow*>(QString("otherTablesWindowDocumentTypes"))) {

        QMdiSubWindow * tmp = ui->mdiArea->addSubWindow(new otherTablesWindow(0, otherTablesWindow::document_types));

        tmp->setWindowIcon(QIcon(QPixmap(":/icons/TablesheetIcon32.png")));
        tmp->setWindowTitle(QString("Документы"));

        tmp->show();
    }
    else {
        qDebug() << "otherTablesWindow[DocumentTypes] is already opened!";
    }
}
void mMainWindow::startRange() {

    QString tmpPath = QFileDialog::getSaveFileName();

    if (tmpPath.isEmpty())
        return;

    QSqlQuery tmpQ(QSqlDatabase::database(DBName));
    qDebug() << tmpQ.exec("select * from range()");

    printOrder(och, buj, tmpPath);
    printOrder(zch, buj, tmpPath);
    printOrder(och, com, tmpPath);
    printOrder(zch, com, tmpPath);

}

void mMainWindow::printOrder(educ_typ typ, educ_form form, QString path) {

    QString typS = typ == och ? QString("очное") : QString("заочное");
    QString formS = form == buj ? QString("бюджет") : QString("платное");

    QSqlTableModel * stm = new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
    stm->setTable("specialities_sets");
    stm->setFilter(QString("(educ_form = '%1' AND finance_form = '%2') AND (entry_score NOTNULL OR half_entry_score NOTNULL)").arg(typS).arg(formS));
    stm->select();

    if (!stm->rowCount()) {
        QMessageBox::warning(0, "Уведомление", QString("Ни один студент не был зачислен на специальности в связке %1 и %2!")
                             .arg(typS).arg(formS));
        return;
    }

    QPdfWriter pdfWriter(path + QString("(%1, %2)").arg(typS).arg(formS) + QString(".pdf"));//tmp + ".pdf");
    QPainter p(&pdfWriter);
    QFont tmpF (p.font());
    tmpF.setFamily("Times New Roman");
    tmpF.setPointSize(14);

    p.setFont(tmpF);

    QString tmp2("МИНИСТЕРСТВО ОБРАЗОВАНИЯ И НАУКИ РОССИЙСКОЙ ФЕДЕРАЦИИ\n"
                 "Федеральное государственное бюджетное учреждение высшего образования\n"
                 "«МОСКОВСКИЙ ГОСУДАРСТВЕННЫЙ УНИВЕРСИТЕТ ТЕХНОЛОГИИ И УПРАВЛЕНИЕ имени К.Г.РАЗУМОВСКОГО (Первый казачий университет)»(ФГБОУ ВО «МГУТУ им. К.Г.Разумовского (ПКУ)»)");
    QString clgName("ФГБОУ ВО «Московский государственный университет технологий и управления имени К.Г.РАЗУМОВСКОГО (Первый казачий университет)»");

    // добавлять укороченное имя высшего учебного заведения + тип учреждения (брать из таблицы)

    int RectM = 750;
    QRect tmpR(RectM,0,pdfWriter.width() - RectM*2,2750);
    p.drawText(tmpR, Qt::AlignCenter | Qt::TextWordWrap , tmp2);
    //p.drawRect(tmpR);

    tmpF.setPointSize(15);
    tmpF.setBold(true);
    p.setFont(tmpF);

    tmp2 = "П Р И К А З";

    tmpR = QRect(RectM,2750,pdfWriter.width() - RectM*2,300);

    p.drawText(tmpR, Qt::AlignCenter  | Qt::TextWordWrap , tmp2);

    tmpF.setPointSize(14);
    tmpF.setBold(false);
    p.setFont(tmpF);

    tmpR = QRect(RectM,3650,pdfWriter.width() - RectM*2,300);

    tmp2 = "«____»_________2018г.";

    p.drawText(tmpR, Qt::AlignBottom | Qt::AlignLeft | Qt::TextWordWrap , tmp2);
    //p.drawRect(tmpR);

    tmp2 = "№_______";

    p.drawText(tmpR, Qt::AlignBottom | Qt::AlignRight | Qt::TextWordWrap , tmp2);
    //p.drawRect(tmpR);

    tmpF.setBold(true);
    p.setFont(tmpF);

    tmpR = QRect(RectM,4050,pdfWriter.width() - RectM*2,300);

    tmp2 = "Москва";

    p.drawText(tmpR, Qt::AlignCenter, tmp2);
    //p.drawRect(tmpR);

    tmpR = QRect(RectM,4850,pdfWriter.width() - RectM*2,1200);

    tmp2 = QString("О зачислении абитуриентов по программам среднего\n"
                   "профессионального образования на %1").arg(form == buj ? QString("бюджетные места в\nрамках контрольных цифр приема")
                                                                          : QString("места,\nфинансируемые за счет средств юридических лиц и\nфизических лиц"));

    p.drawText(tmpR, Qt::AlignBottom | Qt::AlignLeft | Qt::TextWordWrap | Qt::AlignJustify, tmp2);

    tmpF.setBold(false);
    p.setFont(tmpF);

    tmpR = QRect(RectM,6050,pdfWriter.width() - RectM*2,1500);

    tmp2 = QString("\t\tВ соответствии с Правилами приема %1 в %2 году на обучение по "
                   "образовательными программам среднего профессионального образования"
                   "в %2-%3 уч.г.").arg(clgName).arg(2017).arg(2018); // вставка имени высшего учебного заведения, дат

    p.drawText(tmpR, Qt::TextWordWrap | Qt::AlignJustify | Qt::TextExpandTabs, tmp2);
    //p.drawRect(tmpR);

    tmpR = QRect(RectM,7350,pdfWriter.width() - RectM*2,300);

    tmpF.setBold(true);
    p.setFont(tmpF);

    tmp2 = QString("ПРИКАЗЫВАЮ:");

    p.drawText(tmpR, Qt::AlignLeft | Qt::AlignVCenter, tmp2);
    //p.drawRect(tmpR);

    tmpF.setBold(false);
    p.setFont(tmpF);

    tmpR = QRect(RectM,7950,pdfWriter.width() - RectM*2,1500);

    tmp2 = QString("\t\tЗачислить с 1 сентября 2017 года на первый курс для обучения по основным "
                   "образовательным программам среднего профессионального образования на места в "
                   "рамках контрольных цифр приема, финансовое обеспечение которых осуществляется за "
                   "счет %1").arg(form == buj ? QString("бюджетных ассигнований федерального бюджета, по %1 форме обучения следующих абитуриентов:").arg(typ == och
                                                                                                                                                           ? QString("очной")
                                                                                                                                                           : QString("заочной"))
                                              : QString("средств юридических и физических лиц, по %1 форме обучения следующих абитуриентов:").arg(typ == och
                                                                                                                                                    ? QString("очной")
                                                                                                                                                    : QString("заочной")));

    p.drawText(tmpR, Qt::TextWordWrap | Qt::AlignJustify | Qt::TextExpandTabs, tmp2);
    //p.drawRect(tmpR);

    tmpR = QRect(RectM,9500,pdfWriter.width() - RectM*2,300);

    tmp2 = QString("Приложение 1 - %1").arg("Университетский колледж информационных технологий"); // вставить имя колледжа

    p.drawText(tmpR, Qt::AlignCenter, tmp2);
    //p.drawRect(tmpR);

    tmpF.setBold(true);
    p.setFont(tmpF);

    tmpR = QRect(RectM,pdfWriter.height() - 500,pdfWriter.width() - RectM*2,300);

    tmp2 = QString("Ректор");

    p.drawText(tmpR, Qt::AlignLeft, tmp2);
    //p.drawRect(tmpR);

    tmpR = QRect(RectM,pdfWriter.height() - 650,pdfWriter.width() - RectM*2,300);

    tmp2 = QString("%1").arg("В.Н.Иванова"); // вставить имя ректора

    p.drawText(tmpR, Qt::AlignRight, tmp2);
    //p.drawRect(tmpR);

    tmpF.setBold(false);
    p.setFont(tmpF);

    // ПЕЧАТЬ ЗАЧИСЛЕННЫХ!
    //------------------------------------------------------------------------------

    int counter = stm->rowCount();

    pdfWriter.newPage();

    int rectVM = 150;
    int pageCounter = 2;

    tmpR = QRect(RectM, rectVM ,pdfWriter.width() - RectM*2,600);
    tmp2 = QString("Приложение 1 к приказу ______от ________О зачислении абитуриентов в %1")
            .arg("Университетский колледж информационных технологий");

    p.drawText(tmpR, Qt::AlignRight | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM, pdfWriter.height() - 600 ,pdfWriter.width() - RectM*2,300);
    tmp2 = QString("%1")
            .arg(pageCounter++);

    p.drawText(tmpR, Qt::AlignRight, tmp2);



    while (counter--) {

        QSqlTableModel * etm =  new QSqlTableModel(this, QSqlDatabase::database(QString(DBName)));
        etm->setTable(QString("range_result_set_%1_v").arg(stm->record(counter).value("set_id").toString()));
        etm->select();

        int set_id = stm->record(counter).value("spec_id").toInt();

        qDebug() << set_id;

        QSqlTableModel * spectm =  new QSqlRelationalTableModel(this, QSqlDatabase::database(QString(DBName)));
        spectm->setTable("specialities");
        spectm->setFilter(QString("spec_id = %1").arg(QString::number(set_id)));
        spectm->select();

        rectVM += tmpR.height() + 100;

        if (rectVM + 600 > pdfWriter.height() - 600) {

            pdfWriter.newPage();
            rectVM = 150;

            tmpR = QRect(RectM, rectVM ,pdfWriter.width() - RectM*2,1200);
            tmp2 = QString("Приложение 1 к приказу ______от ________О зачислении абитуриентов в %1")
                    .arg("Университетский колледж информационных технологий");

            p.drawText(tmpR, Qt::AlignRight | Qt::TextWordWrap, tmp2);

            tmpR = QRect(RectM, pdfWriter.height() - 600 ,pdfWriter.width() - RectM*2,300);
            tmp2 = QString("%1")
                    .arg(pageCounter++);

            p.drawText(tmpR, Qt::AlignRight, tmp2);

        }

        tmpR = QRect(RectM, rectVM, pdfWriter.width() - RectM*2,600);
        tmp2 = QString("По специальности %1 «%2»")
                .arg(spectm->record(0).value("code").toString()).arg(spectm->record(0).value("name").toString());

        //qDebug << tmpR.height();

        p.drawText(tmpR, Qt::AlignHCenter | Qt::AlignBottom, tmp2);

        int ent_count = etm->rowCount();

        // ширина столбца
        int  rectHM = 1750;

        rectVM += tmpR.height();

        tmpF.setBold(true);
        p.setFont(tmpF);

        tmpR = QRect(RectM - 500, rectVM ,rectHM,300);
        tmp2 = QString("№ п/п");
        p.drawText(tmpR, Qt::AlignCenter, tmp2);
        p.drawRect(tmpR);

        tmpR = QRect(RectM - 500 + rectHM * 1, rectVM ,rectHM,300);
        tmp2 = QString("Фамилия");
        p.drawText(tmpR, Qt::AlignCenter, tmp2);
        p.drawRect(tmpR);

        tmpR = QRect(RectM - 500 + rectHM * 2, rectVM ,rectHM,300);
        tmp2 = QString("Имя");
        p.drawText(tmpR, Qt::AlignCenter, tmp2);
        p.drawRect(tmpR);

        tmpR = QRect(RectM - 500  + rectHM * 3, rectVM ,rectHM,300);
        tmp2 = QString("Отчество");
        p.drawText(tmpR, Qt::AlignCenter, tmp2);
        p.drawRect(tmpR);

        tmpR = QRect(RectM - 500  + rectHM * 4, rectVM ,rectHM,300);
        tmp2 = QString("Средний балл");
        p.drawText(tmpR, Qt::AlignCenter, tmp2);
        p.drawRect(tmpR);

        tmpF.setBold(false);
        p.setFont(tmpF);

        int entc = 0;

        etm->setSort(etm->record().indexOf("score"), Qt::AscendingOrder);
        etm->select();

        while (ent_count--) {
            QApplication::processEvents();

            rectVM += tmpR.height();

            if (rectVM + 300 > pdfWriter.height() - 600) {

                pdfWriter.newPage();
                rectVM = 150;

                tmpR = QRect(RectM, rectVM ,pdfWriter.width() - RectM*2,600);
                tmp2 = QString("Приложение 1 к приказу ______от ________О зачислении абитуриентов в %1")
                        .arg("Университетский колледж информационных технологий");

                p.drawText(tmpR, Qt::AlignRight | Qt::TextWordWrap, tmp2);

                tmpR = QRect(RectM, pdfWriter.height() - 600 ,pdfWriter.width() - RectM*2,300);
                tmp2 = QString("%1")
                        .arg(pageCounter++);

                p.drawText(tmpR, Qt::AlignRight, tmp2);

                rectVM += tmpR.height();
            }

            tmpR = QRect(RectM - 500, rectVM ,rectHM,300);
            tmp2 = QString("%1")
                    .arg(++entc);

            p.drawText(tmpR, Qt::AlignCenter, tmp2);
            p.drawRect(tmpR);

            tmpR = QRect(RectM - 500 + rectHM * 1, rectVM ,rectHM,300);
            tmp2 = QString("%1")
                    .arg(etm->record(ent_count).value("sec_name").toString());

            p.drawText(tmpR, Qt::AlignCenter, tmp2);
            p.drawRect(tmpR);

            tmpR = QRect(RectM - 500 + rectHM * 2, rectVM ,rectHM,300);
            tmp2 = QString("%1")
                    .arg(etm->record(ent_count).value("name").toString());

            p.drawText(tmpR, Qt::AlignCenter, tmp2);
            p.drawRect(tmpR);

            tmpR = QRect(RectM - 500  + rectHM * 3, rectVM ,rectHM,300);
            tmp2 = QString("%1")
                    .arg(etm->record(ent_count).value("mid_name").toString());

            p.drawText(tmpR, Qt::AlignCenter, tmp2);
            p.drawRect(tmpR);

            tmpR = QRect(RectM - 500  + rectHM * 4, rectVM ,rectHM,300);
            tmp2 = QString("%1")
                    .arg(etm->record(ent_count).value("score").toString());

            p.drawText(tmpR, Qt::AlignCenter, tmp2);
            p.drawRect(tmpR);
        }
    }

    pdfWriter.newPage();

    tmpR = QRect(RectM, pdfWriter.height() - 600 ,pdfWriter.width() - RectM*2,300);
    tmp2 = QString("%1")
            .arg(pageCounter++);

    p.drawText(tmpR, Qt::AlignRight, tmp2);

    tmpF.setBold(true);
    p.setFont(tmpF);

    tmpR = QRect(RectM, 0, pdfWriter.width() - RectM*2,600);
    tmp2 = QString("Лист согласования");

    p.drawText(tmpR, Qt::AlignCenter, tmp2);

    tmpR = QRect(RectM, 700, pdfWriter.width() * 0.60 - RectM*2,700);
    tmp2 = QString("Проект вносит:");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 700, pdfWriter.width() - RectM*2,700);
    tmp2 = QString("Согласовано:");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpF.setBold(false);
    p.setFont(tmpF);

    tmpR = QRect(RectM, 1200, pdfWriter.width() * 0.60 - RectM*2,700);
    tmp2 = QString("Ответственный секретарь приемной комиссии");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 1200, pdfWriter.width() - RectM*2,700);
    tmp2 = QString("Первый ректор");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM, 1800, pdfWriter.width() * 0.60 - RectM*2,300);
    tmp2 = QString("________________%1").arg("Г.В. Язев");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 1800, pdfWriter.width() - RectM*2,300);
    tmp2 = QString("________________%1").arg("Г.П. Капица");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM, 2100, pdfWriter.width() * 0.60 - RectM*2,300);
    tmp2 = QString("«____»__________%1").arg("2017 г.");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 2100, pdfWriter.width() - RectM*2,300);
    tmp2 = QString("«____»__________%1").arg("2017 г.");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);


    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 2700, pdfWriter.width() - RectM*2,300);
    tmp2 = QString("Директор колледжа");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 3000, pdfWriter.width() - RectM*2,300);
    tmp2 = QString("________________%1").arg("Р.В. Александров");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    tmpR = QRect(RectM + pdfWriter.width() * 0.50 , 3300, pdfWriter.width() - RectM*2,300);
    tmp2 = QString("«____»__________%1").arg("2017 г.");

    p.drawText(tmpR, Qt::AlignLeft | Qt::TextWordWrap, tmp2);

    p.end();
}

#include "mmainwindow.h"
#include "mentrydialog.h"
#include "maddabiturdialog.h"
#include <QApplication>
#include <QtSql>
#include "maddabiturdocsdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mEntryDialog * c = new mEntryDialog();
    mMainWindow w;
    QObject::connect(c, mEntryDialog::dbConnected,
                     &w, mMainWindow::show);

    c->exec();

    return a.exec();
}

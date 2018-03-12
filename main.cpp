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
    mMainWindow* mp;

    if (c->exec() == QDialog::Accepted) {
      mp = new mMainWindow();
      mp->show();
    }
    else {
      exit(0);
    }

    return a.exec();
}

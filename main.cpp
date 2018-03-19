#include "mmainwindow.h"
#include "mentrydialog.h"
#include "maddabiturdialog.h"
#include <QApplication>
#include <QtSql>
#include "maddabiturdocsdialog.h"
#include <QPdfWriter>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mEntryDialog * c = new mEntryDialog();
    mMainWindow* mp;

    QPdfWriter pw("test.pdf");
    pw.setPageSize(QPdfWriter::A4);
    pw.newPage();
    QPainter p(&pw);
    QFont f;
    f.setFamily("Times New Roman");
    f.setPointSize(14);
    p.setFont(f);
    QString text;
    text += "ФГБОУ ВО Московский государственный университет технологий"
            "и управления имени К.Г. Разумовского (Первый казачий университет)."
            "Университетский колледж информационных технологий";

    p.drawText(QRect(10,10,pw.width(),3000), Qt::AlignCenter | Qt::TextWordWrap, text);
    p.end();

    if (c->exec() == QDialog::Accepted) {
      mp = new mMainWindow();
      mp->show();
    }
    else {
      exit(0);
    }

    return a.exec();
}

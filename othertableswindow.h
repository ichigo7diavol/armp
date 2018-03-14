#ifndef OTHERTABLESWINDOW_H
#define OTHERTABLESWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "mmainwindow.h"
#include "madddisciplinedialog.h"
#include "maddbenifitdialog.h"
#include "precompileconstants.h"


namespace Ui {
class otherTablesWindow;
}

class otherTablesWindow : public QMainWindow
{
    Q_OBJECT

public:

    enum otherTablesWinTypes {
        benefits,
        disciplines,
        document_types,
        specialities,
        specialities_sets
    };

    explicit otherTablesWindow(QWidget *parent = 0);

    explicit otherTablesWindow(QWidget *parent,
                               otherTablesWinTypes);
    ~otherTablesWindow();

public slots:
    void addRowButton();
    void addRow(QList<QVariant> &);

    void editRowButton();
    void editRow(QList<QVariant> &);

    void deleteRowButton();

private:
    Ui::otherTablesWindow *ui;

    otherTablesWinTypes ct; // current table

    QSqlTableModel * ptm;
    QSqlTableModel * pptm;
};

#endif // OTHERTABLESWINDOW_H

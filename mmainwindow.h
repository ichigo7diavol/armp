#ifndef MMAINWINDOW_H
#define MMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include <QDebug>
#include <QMdiSubWindow>
#include <QtSql>
#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QPrinter>
#include <QPdfWriter>
#include <QPrinter>

#include "mabiturtablewindow.h"
#include "othertableswindow.h"
#include "mestablishmenteditdialog.h"

namespace Ui {
class mMainWindow;
}

class mMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mMainWindow(QWidget *parent = 0);
    ~mMainWindow();

private:
    Ui::mMainWindow * ui;

    enum educ_typ {och, zch};
    enum educ_form {buj, com};

public slots:
    void openAbiturientsTable ();
    void openDisciplineTable();
    void openSpecialitiesTable();
    void openSpecialitiesSetsTable();
    void openBenefitsTable();
    void openDocumentTypesTable();
    void startRange();
    void printOrder(educ_typ typ, educ_form form, QString path);
    void openEstablishmentDialog();
};

#endif // MMAINWINDOW_H

#ifndef MABITURTABLEWINDOW_H
#define MABITURTABLEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>

#include "maddspecdialog.h"
#include "maddabiturdocsdialog.h"
#include "maddexamdialog.h"
#include "precompileconstants.h"
#include "maddabiturdialog.h"

namespace Ui {
class mAbiturTableWindow;
}

class mAbiturTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mAbiturTableWindow(QWidget *parent = 0);
    ~mAbiturTableWindow();

public slots:
    void addRowButton();
    void addRow(QList <QVariant> &);

    void deleteRowButton();
    void editRowButton();
    void editRow(QList <QVariant> &);
    void copyRowButton();

    void changeSubTable (int index);

    void abiturChanged();

private:
    Ui::mAbiturTableWindow *ui; // ui
    QSqlRelationalTableModel * ptm; // ptr to main table model
    QSqlTableModel * pptm;

    QComboBox * tableSwitcher;

    QSqlRelationalTableModel * pstm; // sub table model
    QSqlTableModel * ppstm; // sub table model for editing

    QVector <int> hci; // hidden column index
    QVector <int> sci; // showed column index

    QVector <QString> ehci; // ex
    QVector <QString> esci;

    QVector <QString> dhci; // docs
    QVector <QString> dsci;

    QVector <QString> shci; // specs
    QVector <QString> ssci;

    enum sunWinType { none = -1, exams = 0, documents, specialities } swt;
};

#endif // MABITURTABLEWINDOW_H

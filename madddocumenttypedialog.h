#ifndef MADDDOCUMENTTYPEDIALOG_H
#define MADDDOCUMENTTYPEDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class mAddDocumentTypeDialog;
}

class mAddDocumentTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddDocumentTypeDialog(QWidget *parent = 0);
    ~mAddDocumentTypeDialog();

signals:
    void cortegeFormed(QList<QVariant>&);

public slots:
    void formCortege();
    void fillCortege(const QSqlRecord &);


private:
    Ui::mAddDocumentTypeDialog *ui;
};

#endif // MADDDOCUMENTTYPEDIALOG_H

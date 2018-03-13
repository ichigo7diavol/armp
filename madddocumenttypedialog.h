#ifndef MADDDOCUMENTTYPEDIALOG_H
#define MADDDOCUMENTTYPEDIALOG_H

#include <QDialog>

namespace Ui {
class mAddDocumentTypeDialog;
}

class mAddDocumentTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mAddDocumentTypeDialog(QWidget *parent = 0);
    ~mAddDocumentTypeDialog();

private:
    Ui::mAddDocumentTypeDialog *ui;
};

#endif // MADDDOCUMENTTYPEDIALOG_H

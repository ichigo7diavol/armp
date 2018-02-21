#ifndef MABITURTABLE_H
#define MABITURTABLE_H

#include <QWidget>

namespace Ui {
class mAbiturTable;
}

class mAbiturTable : public QWidget
{
    Q_OBJECT

public:
    explicit mAbiturTable(QWidget *parent = 0);
    ~mAbiturTable();

private:
    Ui::mAbiturTable *ui;
};

#endif // MABITURTABLE_H

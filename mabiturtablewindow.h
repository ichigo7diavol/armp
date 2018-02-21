#ifndef MABITURTABLEWINDOW_H
#define MABITURTABLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class mAbiturTableWindow;
}

class mAbiturTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mAbiturTableWindow(QWidget *parent = 0);
    ~mAbiturTableWindow();

private:
    Ui::mAbiturTableWindow *ui;
};

#endif // MABITURTABLEWINDOW_H

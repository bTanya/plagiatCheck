#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "plagiarismThread.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
public slots:
    void endProcessing();

private:
    Ui::Widget *ui;
    QString nameFirstFile,nameSecondFile;
    PlagiarismThread * myThread;
};

#endif // WIDGET_H

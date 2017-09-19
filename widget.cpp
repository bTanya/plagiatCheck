#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    Widget::setWindowTitle("PLAGIARISM CHECKS");


}

Widget::~Widget()
{
    delete ui;
}
void Widget::endProcessing()
{
    if(myThread -> isRunning())
    {
        myThread -> exit();
    }
    delete myThread;
    myThread = 0;

}
void Widget::on_pushButton_clicked()
{
    nameFirstFile =  QFileDialog::getOpenFileName(0,
                                                  QObject::tr("Укажите файл для сравнения"),
                                                  QCoreApplication::applicationDirPath (),
                                                  QObject::tr("Файл исходных кодов (*.*);;"));
    if (true == nameFirstFile.isEmpty()) {
        return;
    }
    ui->lineEdit->setText(nameFirstFile);

}

void Widget::on_pushButton_2_clicked()
{
    nameSecondFile =  QFileDialog::getOpenFileName(0,
                                                   QObject::tr("Укажите файл для сравнения"),
                                                   QCoreApplication::applicationDirPath (),
                                                   QObject::tr("Файл исходных кодов (*.*);;"));
    if (true == nameSecondFile.isEmpty()) {
        return;
    }
    ui->lineEdit_2->setText(nameSecondFile);

}

void Widget::on_pushButton_3_clicked()
{
    ui->progressBar->setVisible(true);
    myThread = new PlagiarismThread(nameFirstFile,nameSecondFile);
    connect(myThread, &PlagiarismThread::progressChanged,ui->progressBar, &QProgressBar::setValue);
    myThread->start();
    QObject::connect(myThread, &PlagiarismThread::getResultAnalysis,ui->lineEdit_3, &QLineEdit::setText);
    connect(myThread, &PlagiarismThread::runFineshed, myThread, &PlagiarismThread::deleteLater);
    connect(myThread, &PlagiarismThread::runFineshed, this, &Widget::endProcessing);
}

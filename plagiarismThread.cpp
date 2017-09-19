#include "plagiarismThread.h"
#include <math.h>
#include <QProgressBar>

PlagiarismThread::PlagiarismThread(QString nameFirsFile,QString nameSecondFile)
{
    this->nameFirsFile = nameFirsFile;
    this->nameSecondFile = nameSecondFile;
}
unsigned int PlagiarismThread::findJaccardIndex(QStringList first, QStringList second)
{

    first+= second;
    float intersection,combination=first.size();;
    first.removeDuplicates();
    intersection=combination-first.size();
    ////qDebug()<<intersection/combination;
    combination=first.size();
    return ((intersection/combination)*100);

}

void PlagiarismThread::run()
{
    emit progressChanged(0);
    QFile token("C:\\tmp\\token.xml");
        bool open = token.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!open)
        {
            qDebug()<< "Couldn't open  token file" <<"\n";
            return ;
        }
        else
        {
            qDebug( )<< "File token opened OK" <<"\n";
        }
        QFile file(this->nameFirsFile);
        open = file.open(QIODevice::ReadWrite | QIODevice::Text);
        if (!open)
        {
            qDebug()<< "Couldn't open file" <<"\n";
            return ;
        }
        else
        {
            qDebug( )<< "File opened OK" <<"\n";
        }

        QFile file2(this->nameSecondFile);
        open = file2.open(QIODevice::ReadWrite | QIODevice::Text);
        if (!open)
        {
            qDebug()<< "Couldn't open file2" <<"\n";
            return ;
        }
        else
        {
            qDebug( )<< "File opened OK" <<"\n";
        }
        emit progressChanged(5);

        Tokenization genTokenFile1(&token,&file);
        genTokenFile1.tokenizationCode();
        QString checkgenTokenFile1 = genTokenFile1.getTokenString();
        token.close();
        emit progressChanged(50);

        token.setFileName("C:\\tmp\\token.xml");
        open = token.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!open)
        {
            qDebug()<< "Couldn't open token file" <<"\n";
            return ;
        }
        else
        {
            qDebug( )<< "File token opened OK" <<"\n";
        }


        Tokenization genTokenFile2(&token,&file2);
        genTokenFile2.tokenizationCode();
        QString checkgenTokenFile2 = genTokenFile2.getTokenString();

        file.close();
        file2.close();
        token.close();
        emit progressChanged(85);

        QStringList first = genTokenFile1.createSetOfToken(checkgenTokenFile1);
        QStringList second = genTokenFile2.createSetOfToken(checkgenTokenFile2);

        qDebug()<<findJaccardIndex(first,second);
        emit getResultAnalysis(QString::number(findJaccardIndex(first,second)));
        emit progressChanged(100);
        emit runFineshed(true);
}

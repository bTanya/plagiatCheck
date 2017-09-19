#ifndef PLAGIARISMTHREAD_H
#define PLAGIARISMTHREAD_H
#include <QThread>
#include "token.h"

class PlagiarismThread : public QThread
{
    Q_OBJECT
public:
    PlagiarismThread( QString nameFirsFile,QString nameSecondFile);
    void run();
    //QString getResultAnalysis();
private:
    unsigned int findJaccardIndex(QStringList first, QStringList second);
    QString nameFirsFile;
    QString nameSecondFile;
    //QString resultAnalysis;
signals:
    void progressChanged(int val);
    void getResultAnalysis(QString resultAnalysis);
    void runFineshed(bool isEnd);


};


#endif // PLAGIARISMTHREAD_H

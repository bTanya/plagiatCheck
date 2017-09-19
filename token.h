#include <QFile>
#include <QRegExp>
#include <QTextStream>
#include<QXmlStreamReader>
#include <qDebug>
#include <QStringList>
class Tokenization
{
public:
    Tokenization(QFile * token, QFile * file);
    QString getTokenString();
    void tokenizationCode();
    QStringList createSetOfToken(QString tokenString);
private:
    QString textFile;
    QRegExp regExpForOperation;
    QFile *xmlFile;
    void removeLineComments();
    void removeBlockComments();
    void removeString();
    void changeOperands();
    void changeOperators();
    void changeStartStopOperands();
    void removeInclude();
    void changeName();
    void digitalConversionOfTokens();
protected:
   // QStringList createSetOfToken(QString tokenString);
};

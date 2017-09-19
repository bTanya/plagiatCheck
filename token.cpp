#include "token.h"
Tokenization::Tokenization(QFile * token, QFile * file)

{
    QTextStream stream(file);
    this->textFile = stream.readAll();
    xmlFile = token;

}
void Tokenization::removeLineComments()
{
    QXmlStreamReader xml (xmlFile);
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNextStartElement();
        do {
            xml.readNextStartElement();
        } while(xml.name().toString() != "c"); // your must change cons string on selected language

        xml.readNextStartElement();
        do  {
            xml.readNextStartElement();
            if(xml.name() == "c" && xml.isEndElement())
            {
                qErrnoWarning("line comments not found");
                break;
            }
        }  while(xml.name().toString() != "lineComments");
        regExpForOperation.setPattern(xml.readElementText()+".*\n");
        regExpForOperation.setMinimal(true);
        textFile.replace(regExpForOperation,"{LC} \n");
        xml.readNext();
        break;
    }
}
void Tokenization::removeBlockComments()
{
    xmlFile->seek(0);
    QXmlStreamReader xml (xmlFile);

    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNextStartElement();
        do {
            xml.readNextStartElement();
        }  while(xml.name().toString() != "c"); // your must change cons string on selected language

        xml.readNextStartElement();
        do  {
            xml.readNextStartElement();
            if(xml.name() == "c" && xml.isEndElement())
            {
                qErrnoWarning("line comments not found");
                break;
            }
        }  while(xml.name().toString() != "blockCommentsOpen");
        break;
    }
    QString openComment =xml.readElementText(),closeComment;
    xml.readNextStartElement();
    closeComment =  xml.readElementText();
    regExpForOperation.setPattern(openComment+".*"+closeComment);
    textFile.replace(regExpForOperation,"{BC}");
    xml.readNext();
}
void Tokenization::removeString()
{
    textFile.replace('\"',"@");
    regExpForOperation.setPattern( "@.*@" );
    regExpForOperation.setMinimal(true);
    textFile.replace(regExpForOperation,"{S}");
}
void Tokenization::changeOperands()
{
    xmlFile->seek(0);
    QXmlStreamReader xml (xmlFile);
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if (xml.isStartElement())
        {
            QString name = xml.name().toString();
            if(name == "c")
            {
                while(!xml.isEndElement())
                {
                    xml.readNext();
                    name = xml.name().toString();
                    if (name == "operand" )
                    {
                        regExpForOperation.setPattern(xml.readElementText());
                        textFile.replace(regExpForOperation,"{O}");
                        xml.readNext();
                    }
                }
            }
        }
    }
}
void Tokenization::changeOperators()
{
    xmlFile->seek(0);
    QXmlStreamReader xml (xmlFile);
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if (xml.isStartElement())
        {
            QString name = xml.name().toString();
            if(name == "c")
            {
                xml.readNext();
                do{
                    name = xml.name().toString();
                    if (name == "operator")
                    {
                        regExpForOperation.setPattern(xml.readElementText());
                        textFile.replace(regExpForOperation,"{D}");
                    }
                    xml.readNext();
                }while(name != "c");
            }
        }
    }
}
void Tokenization::changeStartStopOperands()
{
    textFile.replace("\{","@#@#@");
    regExpForOperation.setPattern("@#@#@" );
    textFile.replace(regExpForOperation,"START");
    textFile.replace("}","@#@#@");
    regExpForOperation.setPattern( "@#@#@" );
    textFile.replace(regExpForOperation,"END");
    textFile.replace("END","{E}");
    textFile.replace("START","{ST}");
}
void Tokenization::removeInclude()
{
    regExpForOperation.setPattern( "#.*\n" );
    regExpForOperation.setMinimal(true);
    textFile.replace(regExpForOperation,"{I}\n");
}
void Tokenization::changeName()
{
    textFile.replace("{","@");
    textFile.replace("}","#");
    textFile.replace("\n","");
    textFile.replace(" ","");
    regExpForOperation.setPattern("#.{1,}@");
    regExpForOperation.setMinimal(true);
    textFile.replace(regExpForOperation,"}{N}{");
    textFile.replace("@","{");
    textFile.replace("#","}");
}
void Tokenization::digitalConversionOfTokens()
{
    textFile.replace("{LC}","1");
    textFile.replace("{BC}","2");
    textFile.replace("{S}","3");
    textFile.replace("{O}","4");
    textFile.replace("{D}","5");
    textFile.replace("{ST}","6");
    textFile.replace("{E}","7");
    textFile.replace("{I}","8");
    textFile.replace("{N}","9");
}
QString Tokenization::getTokenString()
{
    return textFile;
}
void Tokenization::tokenizationCode()
{
    changeStartStopOperands();
    removeLineComments(); //it work!!!
    removeBlockComments(); //it work!!!
    removeString();// it work!!
    removeInclude();
    changeOperands();  //it work!!!
    changeOperators();  //it work!!!
    changeName();//so work ;(
    digitalConversionOfTokens();
}
QStringList Tokenization::createSetOfToken(QString tokenString)
{
    QString tmp;
    const unsigned char sizeOfToken = 4;
    QStringList tokenList;
    tmp="";
    tokenList.clear();
    for (int i = 0; i < tokenString.length()-4; ++i)
    {
        for (int j = 0,position = i; j < sizeOfToken; ++j, ++position )
        {
            tmp.push_back(tokenString[position]);
        }
        tokenList.push_back(tmp);
        tmp="";
    }
    tokenList.removeDuplicates();
//    for ( QStringList::Iterator it = tokenList.begin(); it != tokenList.end(); ++it )
//           qDebug() << *it << "\n";
  //  qDebug() << "write list" << "\n";
    return tokenList;
}


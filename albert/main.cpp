#include <QCoreApplication>
#include "albert.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    albert myalbert;
    GROUP groups[GROUPS_COUNT] = { { 0 } };

    myalbert.EnumHouseColors(groups, 0);
    //myalbert.test_Checkfunctions();
   // myalbert.mydo();
    return a.exec();
}


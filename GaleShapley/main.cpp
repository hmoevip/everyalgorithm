#include <QCoreApplication>
#include "mygs1.h"
#include "hungarymatch.h"
#include "kuhnmunkres.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#if 0
PARTNER girls[] = {
    PARTNER("A", 0, -1, 4, vector<int> {2,3,1,0}),
    PARTNER("B", 0, -1, 4, vector<int> {2,1,3,0}),
    PARTNER("C", 0, -1, 4, vector<int> {0,2,3,1}),
    PARTNER("D", 0, -1, 4, vector<int> {1,3,2,0})
};

PARTNER boys[] =
{
    PARTNER("1", 0, -1, 4, vector<int> {0,3,2,1}),
    PARTNER("2", 0, -1, 4, vector<int> {0,1,2,3}),
    PARTNER("3", 0, -1, 4, vector<int> {0,2,3,1}),
    PARTNER("4", 0, -1, 4, vector<int> {1,0,3,2})
};
#endif
#if 0

    PARTNER girls[] =
    {
        PARTNER("Laura", 0, -1, 3, vector<int> {2,0,1} ), //Laura
        PARTNER("Marcy", 0, -1, 3, vector<int> {0,2,1} ),  //Marcy
        PARTNER("Nancy", 0, -1, 3, vector<int> {1,0,2} ) //Nancy
    };

    PARTNER boys[] =
    {
        PARTNER("Albert", 0, -1, 3, vector<int> {0,2,1} ), //Albert
        PARTNER("Brad",   0, -1, 3, vector<int> {1,2,0} ), //Brad
        PARTNER("Chuck",  0, -1, 3, vector<int> {0,1,2} ) //Chuck
    };
/*
Albert Laura Nancy Marcy
Brad Marcy Nancy Laura
Chuck Laura Marcy Nancy

Laura Chuck Albert Brad
Marcy Albert Chuck Brad
Nancy Brad Albert Chuck


Albert Nancy
Brad Marcy
Chuck Laura
*/
#endif
#if 0
    PARTNER X[] =
    {
        {"X1", 0, -1, 1, {2} },
        {"X2", 0, -1, 2, {0,1} },
        {"X3", 0, -1, 3, {1,2,3} },
        {"X4", 0, -1, 2, {1,2} },
        {"X5", 0, -1, 3, {2,3,4} }
    };
    PARTNER Y[] =
    {
        {"Y1", 0, -1, 1, {1} },
        {"Y2", 0, -1, 3, {1,2,3} },
        {"Y3", 0, -1, 4, {0,2,3,4} },
        {"Y4", 0, -1, 2, {2,4} },
        {"Y5", 0, -1, 1, {4} }
    };
#endif
#if 1


    /*
        Y1   Y2   Y3   Y4   Y5
    X1  3    5    5    4    1
    X2  2    2    0    2    2
    X3  2    4    4    1    0
    X4  0    1    1    0    0
    X5  1    2    1    3    3
    */
    PARTNER1 X[] =
    {
        {"X1", {3,5,5,4,1} },
        {"X2", {2,2,0,2,2} },
        {"X3", {2,4,4,1,0} },
        {"X4", {0,1,1,0,0} },
        {"X5", {1,2,1,3,3} }
    };
#endif
#if 1
    KM_MATCH km_match;
    kuhnmunkres mymatch;
    mymatch.InitGraph(&km_match, X);
        if(mymatch.Kuhn_Munkres_Match(&km_match))
        {
            mymatch.PrintResult(&km_match);
        }
#endif
#if 0
    GRAPH_MATCH match;
    HungaryMatch mymatch;
    mymatch.InitGraph(&match,X);
    if(mymatch.Hungary_Match(&match))
        {
            mymatch.PrintResult2(&match, X, Y);
            mymatch.PrintResult(&match, X, Y);
        }
#endif
#if 0
    MyGS1 mygs;

    mygs.SearchStableMatch(0, boys, girls);
    qDebug() << "Total Matchs : " << mygs.totalMatch << endl;
    qDebug() << "Stable Matchs : " << mygs.stableMatch << endl;

    if(mygs.Gale_Shapley(boys, girls, UNIT_COUNT))
    {
        mygs.PrintResult(boys, girls, UNIT_COUNT);
    }
#endif
    return a.exec();
}


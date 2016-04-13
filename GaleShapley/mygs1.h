#ifndef MYGS1_H
#define MYGS1_H

#include <stack>
#include <QString>
#include <vector>
#include <QDebug>
using namespace std;

const int UNIT_COUNT = 5;

class PARTNER
{
public:
    PARTNER();
    PARTNER(QString name, int next, int current, int pCount, vector<int> perfect)
    {
        this->name = name;
        this->next = next;
        this->current = current;
        this->pCount = pCount;
        //for(unsigned int i=0 ; i< UNIT_COUNT ; ++i)
            this->perfect = perfect;
    }
public:
    QString name;   //名字
    int next;     //下一个邀请对象
    int current;  //当前舞伴，-1表示还没有舞伴
    int pCount; //偏爱列表中舞伴个数
    vector<int> perfect; //偏爱列表

};

class MyGS1
{
public:
    MyGS1();
    //gs1
    bool IsAllPartnerMatch(PARTNER *partners, int n);
    int FindFreePartner(PARTNER *partners, int n);
    int GetPerfectPosition(PARTNER *partner, int id);
    bool Gale_Shapley(PARTNER *boys, PARTNER *girls, int count);
    void PrintResult(PARTNER *boys, PARTNER *girls, int count);

    //gs2
    void SearchStableMatch(int index, PARTNER *boys, PARTNER *girls);
    bool IsStableMatch(PARTNER *boys, PARTNER *girls);
    bool IsFavoritePartner(PARTNER *partner, int bid);
    bool IsPartnerAssigned(PARTNER *partner);
public:
    int totalMatch;
    int stableMatch;
};

#endif // MYGS1_H

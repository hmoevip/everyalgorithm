#include "mygs1.h"


MyGS1::MyGS1()
{
    totalMatch = 0;
    stableMatch = 0;
}

bool MyGS1::IsAllPartnerMatch(PARTNER *partners, int n)      //其实这个函数没意义，因为如果有current＝－1的，那一定会返回i的值，那么就不会跳出while循环
{
    for(int i = 0; i < n; i++)
    {
        if(partners[i].current == -1)
        {
            return false;
        }
    }

    return true;
}

int MyGS1::FindFreePartner(PARTNER *partners, int n)    //遍历所有男孩，找到还没有伴侣并且偏爱列表里还有没追求过的对象的
{
    for(int i = 0; i < n; i++)
    {
        if((partners[i].current == -1) && (partners[i].next < partners[i].pCount))
        {
            return i;         //返回第几个男孩的编号
        }
    }

    return -1;
}
//这里也是算法一致性处理的一个技巧
int MyGS1::GetPerfectPosition(PARTNER *partner, int id)   //传入某个女孩信息，和要判断是否偏爱的男生id
{
    for(int i = 0; i < partner->pCount; i++)
    {
        if(partner->perfect[i] == id)
        {
            return i;  //返回值越小，说明女士越喜欢
        }
    }

    //返回一个非常大的值，意味着根本排不上对，说明偏爱列表没有这个男生，根本不可能
    return 0x7FFFFFFF;
}

bool MyGS1::Gale_Shapley(PARTNER *boys, PARTNER *girls, int count)
{
    int bid = FindFreePartner(boys, count);
    while(bid >= 0)     //只要有男孩，就是大于0的
    {
        int gid = boys[bid].perfect[boys[bid].next];    //next是从0开始的，找到列表中，男生喜欢的女生
        if(girls[gid].current == -1)           //如果女孩当前没有伴侣，他俩就变一对儿
        {
            boys[bid].current = gid;
            girls[gid].current = bid;
        }
        else
        {
            int bpid = girls[gid].current;        //若女孩有伴侣，找到这个伴侣，比较女孩喜欢哪个
            //女孩喜欢bid胜过其当前舞伴bpid
            if(GetPerfectPosition(&girls[gid], bpid) > GetPerfectPosition(&girls[gid], bid))
            {
                boys[bpid].current = -1; //当前舞伴恢复自由身，男孩被抛弃
                boys[bid].current = gid; //结交新舞伴
                girls[gid].current = bid;
            }
        }
        boys[bid].next++; //无论是否配对成功，对同一个女孩只邀请一次
        bid = FindFreePartner(boys, count);   //循环核，不断的找是否有男孩没有找到女伴
    }

    return IsAllPartnerMatch(boys, count);
}
/*
if((GetPerfectPosition(&girls[gid], bpid) == -1)
    && (GetPerfectPosition(&girls[gid], bid) == -1))
{
    //当前舞伴bpid和bid都不在女孩的喜欢列表中，太糟糕了
    ...
}
else if(GetPerfectPosition(&girls[gid], bpid) == -1)
{
    //当前舞伴bpid不在女孩的喜欢列表中，bid有机会
    ...
}
else if(GetPerfectPosition(&girls[gid], bid) == -1)
{
    //bid不在女孩的喜欢列表中，当前舞伴bpid维持原状
    ...
}
else if(GetPerfectPosition(&girls[gid], bpid) > GetPerfectPosition(&girls[gid], bid))
{
    //女孩喜欢bid胜过其当前舞伴bpid
    ...
}
else
{
    //女孩喜欢当前舞伴bpid胜过bid
    ...
}
*/


void MyGS1::PrintResult(PARTNER *boys, PARTNER *girls, int count)
{
    for(int i = 0; i < count; i++)
    {
        qDebug() << boys[i].name << "["
                  << GetPerfectPosition(&boys[i], boys[i].current)
                  << "] <---> " << girls[boys[i].current].name << "["
                  << GetPerfectPosition(&girls[boys[i].current], i)
                  << "]" << endl;
    }
    qDebug() << endl;
}

bool MyGS1::IsPartnerAssigned(PARTNER *partner)
{
    return (partner->current != -1);
}

bool MyGS1::IsFavoritePartner(PARTNER *partner, int bid)
{
    for(int i = 0; i < partner->pCount; i++)
    {
        if(partner->perfect[i] == bid)
        {
            return true;
        }
    }

    return false;
}

bool MyGS1::IsStableMatch(PARTNER *boys, PARTNER *girls)
{
    for(int i = 0; i < UNIT_COUNT; i++)
    {
        //找到男孩当前舞伴在自己的偏好列表中的位置
        int gpos = GetPerfectPosition(&boys[i], boys[i].current);
        //在position位置之前的舞伴，男孩喜欢她们胜过current
        for(int k = 0; k < gpos; k++)    //寻找该男孩偏爱列表在当前女友前面的女生中有没有更喜欢他的
        {
            int gid = boys[i].perfect[k];
            //找到男孩在这个女孩的偏好列表中的位置
            int bpos = GetPerfectPosition(&girls[gid], i);
            //找到女孩的当前舞伴在这个女孩的偏好列表中的位置
            int cpos = GetPerfectPosition(&girls[gid], girls[gid].current);
            if(bpos < cpos)
            {
                //女孩也是喜欢这个男孩胜过喜欢自己当前的舞伴，这是不稳定因素
                return false;
            }
        }
    }

    return true;
}

void MyGS1::SearchStableMatch(int index, PARTNER *boys, PARTNER *girls)    //递归的方法
{
    if(index == UNIT_COUNT)       //递归到了某个分支的终点，此时匹配结果一定是完全匹配，但不一定是稳定匹配
    {
        totalMatch++;
        if(IsStableMatch(boys, girls))  //是否存在不稳定因素，如果没有，就是稳定匹配
        {
            stableMatch++;
            PrintResult(boys, girls, UNIT_COUNT);
        }
        return;
    }

    for(int i = 0; i < boys[index].pCount; i++)     //index随递归过程变大
    {
        int gid = boys[index].perfect[i];

        if(!IsPartnerAssigned(&girls[gid]) && IsFavoritePartner(&girls[gid], index))   //如果女孩没有对象，并且男孩在女孩的偏爱列表里
        {
            boys[index].current = gid;
            girls[gid].current = index;
            SearchStableMatch(index + 1, boys, girls);
            boys[index].current = -1;       //下一层递归回来后，要把前面的假设条件干掉，才能继续同层的循环
            girls[gid].current = -1;
        }
    }
}

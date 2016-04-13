#include "hungarymatch.h"

HungaryMatch::HungaryMatch()
{

}


bool HungaryMatch::FindAugmentPath(GRAPH_MATCH *match, int xi)
{
    for(int yj = 0; yj < UNIT_COUNT; yj++)
    {
        if((match->edge[xi][yj] == 1) && !match->on_path[yj])    //二部图中有这样一条边（即yj是xi的邻接点），并且Y中的该点不在增广路径上
        {
            match->on_path[yj] = true;         //把Y中该点加入增广路径上
            if( (match->path[yj] == -1)        //Y中该点是否是未覆盖点（即没有边连接它）
                || FindAugmentPath(match, match->path[yj]) )  //或者连向该点的X中的点可以找到增广路径
            {
                match->path[yj] = xi;    //把yj加入增广路径，这个路径是xi<－>yj
                return true;       //找到增广路径
            }
        }
    }

    return false;
}


void HungaryMatch::ClearOnPathSign(GRAPH_MATCH *match)
{
    for(int i = 0; i < UNIT_COUNT; i++)
    {
        match->on_path[i] = false;     //把所有的路径上的点清空
    }
}

bool HungaryMatch::Hungary_Match(GRAPH_MATCH *match)
{
    for(int xi = 0; xi < UNIT_COUNT; xi++)
    {
        if(FindAugmentPath(match, xi))    //从X中的第一个点开始找增广路径
        {
            match->max_match++;       //如果找到了，就把增广路径上点的数量加1
        }

        ClearOnPathSign(match);    //过程量，每从一个X出发找到后，就要清空，为下一次寻找做准备
    }
    return (match->max_match == UNIT_COUNT);
}

void HungaryMatch::InitGraph(GRAPH_MATCH *match, PARTNER *X)   //初始化匹配图
{
    match->max_match = 0;
    memset(match->edge, 0, UNIT_COUNT * UNIT_COUNT * sizeof(int));    //数组初始化为0
    for(int i = 0; i < UNIT_COUNT; i++)        //遍历X中的所有节点
    {
        match->on_path[i] = false;            //初始化增广路径，都设为空，这里的i其实是表示Y的下标
        match->path[i] = -1;
        for(int j = 0; j < X[i].pCount; j++)
            match->edge[i][X[i].perfect[j]] = 1;     //得到完整的二部图
    }
}

void HungaryMatch::PrintResult(GRAPH_MATCH *match, PARTNER *X, PARTNER *Y)
{
    for(int i = 0; i < match->max_match; i++)
    {
        qDebug() << X[match->path[i]].name << "<--->" << Y[i].name << endl;
    }
}

void HungaryMatch::PrintResult2(GRAPH_MATCH *match, PARTNER *X, PARTNER *Y)
{
    int path[UNIT_COUNT] = { 0 };

    for(int i = 0; i < match->max_match; i++)
    {
        path[match->path[i]] = i;
    }
    for(int i = 0; i < match->max_match; i++)
    {
        qDebug() << X[i].name << "<--->" << Y[path[i]].name << endl;
    }
}


#ifndef HUNGARYMATCH_H
#define HUNGARYMATCH_H
#include "mygs1.h"

//const int UNIT_COUNT = 5;

typedef struct tagMaxMatch
{
    int edge[UNIT_COUNT][UNIT_COUNT];  //顶点与边的关系
    bool on_path[UNIT_COUNT];     //Y是否在增广路径上
    int path[UNIT_COUNT];        //找到的增广路径
    int max_match;
}GRAPH_MATCH;

class HungaryMatch
{
public:
    HungaryMatch();
    bool FindAugmentPath(GRAPH_MATCH *match, int xi);
    void ClearOnPathSign(GRAPH_MATCH *match);
    bool Hungary_Match(GRAPH_MATCH *match);
    void InitGraph(GRAPH_MATCH *match, PARTNER *X);
    void PrintResult(GRAPH_MATCH *match, PARTNER *X, PARTNER *Y);
    void PrintResult2(GRAPH_MATCH *match, PARTNER *X, PARTNER *Y);
};

#endif // HUNGARYMATCH_H

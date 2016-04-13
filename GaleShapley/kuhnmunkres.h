#ifndef KUHNMUNKRES_H
#define KUHNMUNKRES_H

#include "mygs1.h"
const int INFINITE = 100000000; // 相对无穷大

typedef struct tagPartner
{
    QString name;   //名字
    int weight[UNIT_COUNT];
}PARTNER1;

typedef struct tagKmMatch
{
    int edge[UNIT_COUNT][UNIT_COUNT]; //Xi与Yj对应的边的权重
    bool sub_map[UNIT_COUNT][UNIT_COUNT];// 二分图的相等子图, sub_map[i][j] = 1 代表Xi与Yj有边
    bool x_on_path[UNIT_COUNT]; // 标记在一次寻找增广路径的过程中，Xi是否在增广路径上
    bool y_on_path[UNIT_COUNT]; // 标记在一次寻找增广路径的过程中，Yi是否在增广路径上
    int path[UNIT_COUNT]; // 匹配信息，其中i为Y中的顶点标号，path[i]为X中顶点标号
}KM_MATCH;

class kuhnmunkres
{
public:
    kuhnmunkres();
    bool FindAugmentPath(KM_MATCH *km, int xi);
    void ResetMatchPath(KM_MATCH *km);
    void ClearOnPathSign(KM_MATCH *km);
    bool Kuhn_Munkres_Match(KM_MATCH *km);
    void InitGraph(KM_MATCH *km, PARTNER1 *X);
    void PrintResult(KM_MATCH *km);
};

#endif // KUHNMUNKRES_H

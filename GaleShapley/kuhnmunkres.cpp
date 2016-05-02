#include "kuhnmunkres.h"

kuhnmunkres::kuhnmunkres()
{

}

//总的思路就是匈牙利算法的基础上，先找到最大权值边，进行匈牙利算法，不是最大匹配的时候，再把次大权值的边加入，再进行匈牙利算法，直到得到最大匹配
//或者，所有的边都加入了，但依然没有找到最大匹配

// 在相等子图中寻找Xi为起点的增广路径
bool kuhnmunkres::FindAugmentPath(KM_MATCH *km, int xi)
{
   for(int yj = 0; yj < UNIT_COUNT; yj++)
   {
       if(!km->y_on_path[yj] && km->sub_map[xi][yj])   //如果yj不在增广路径上，并且存在这样一条边
      {
         km->y_on_path[yj] = true;
         int xt = km->path[yj];
         km->path[yj] = xi;
         if(xt == -1 || FindAugmentPath(km, xt))
         {
            return true;
         }
         km->path[yj] = xt;
         if(xt != -1)      //此处说明xt不是未覆盖点，也就是说，该点在增广路径上
             km->x_on_path[xt] = true;    //说明这个xt点在
      }
   }

   return false;
}

void kuhnmunkres::ResetMatchPath(KM_MATCH *km)
{
    for(int i = 0; i < UNIT_COUNT; i++)
    {
        km->path[i] = -1;
    }
}

void kuhnmunkres::ClearOnPathSign(KM_MATCH *km)
{
    for(int i = 0; i < UNIT_COUNT; i++)
    {
        km->x_on_path[i] = false;
        km->y_on_path[i] = false;
    }
}

bool kuhnmunkres::Kuhn_Munkres_Match(KM_MATCH *km)
{
    int i, j;
    int A[UNIT_COUNT], B[UNIT_COUNT];
    // 初始化Xi与Yi的顶标
    for(i = 0; i < UNIT_COUNT; i++)
    {
        B[i] = 0;
        A[i] = -INFINITE;    //负无穷大
        for(j = 0; j < UNIT_COUNT; j++)
        {
            A[i] = std::max(A[i], km->edge[i][j]);   //找到每个X中的节点权值最大的值，这里是理解的关键，因为这里将a设定为最大的，所以之后想扩大，就要让a取小值
        }
    }
    while(true)
    {
        // 初始化带权二分图的相等子图
        for(i = 0; i < UNIT_COUNT; i++)
        {
            for(j = 0; j < UNIT_COUNT; j++)
            {
                km->sub_map[i][j] = ((A[i]+B[j]) == km->edge[i][j]);    //最初B就是0，权值最大的边，算做一条边，
                                //之后，x在a不变，y不在，b变小，和就小，才有可能出现==的情况，因为最大的edge开始的时候已经比过了
            }
        }
        //使用匈牙利算法寻找相等子图的完备匹配
        int match = 0;
        ResetMatchPath(km);    //清空当前匹配情况，为了不断循环使用
        for(int xi = 0; xi < UNIT_COUNT; xi++)
        {
            ClearOnPathSign(km);    //情况x，y加入路径情况，为了循环用
            if(FindAugmentPath(km, xi))
                match++;
            else
            {
                km->x_on_path[xi] = true;   //找过的点xi如果不在增广路径上
                break;
            }
        }
        //如果找到完备匹配就返回结果
        if(match == UNIT_COUNT)
        {
            return true;
        }
        //调整顶标，继续算法
        int dx = INFINITE;
        for(i = 0; i < UNIT_COUNT; i++)
        {
            if(km->x_on_path[i])
            {
                for(j = 0; j < UNIT_COUNT; j++)
                {
                    if(!km->y_on_path[j])    //根据不在增广路径上的点算出一个最小差值
                        dx = std::min(dx, A[i] + B[j] - km->edge[i][j]);
                }
            }
        }
        for(i = 0; i < UNIT_COUNT; i++)    //对所有在增广路径上的点都左减，右加，这样，1.原来增广路径上的点，权值不变；
                                            //2.原来都不在的，权值不变；3.x在，y不在的，权值变小,保留；4.x不在，y在的，权值变大
        {
            if(km->x_on_path[i])
                A[i] -= dx;
            if(km->y_on_path[i])
                B[i] += dx;
        }
    }

    return false;
}




void kuhnmunkres::InitGraph(KM_MATCH *km, PARTNER1 *X)
{
    memset(km->edge, 0, UNIT_COUNT * UNIT_COUNT * sizeof(int));
    for(int i = 0; i < UNIT_COUNT; i++)
    {
        km->path[i] = -1;
        for(int j = 0; j < UNIT_COUNT; j++)
            km->edge[i][j] = X[i].weight[j];   //初始化每条边，已有边赋权值
    }
}

void kuhnmunkres::PrintResult(KM_MATCH *km)
{
    int cost = 0;
    for(int i = 0; i < UNIT_COUNT; i++)
    {
        cost += km->edge[km->path[i]][i];
        qDebug() << "x" << km->path[i] << "<--->" << "y" << i << endl;
    }

    qDebug() << "total cost : " << cost << endl;
}


#include "bucket_state.h"
#include <QDebug>

int bucket_capicity[BUCKETS_COUNT] = {8, 5, 3};
int bucket_init_state[BUCKETS_COUNT]  = {8, 0, 0};
int bucket_final_state[BUCKETS_COUNT] = {4, 4, 0};

BucketState::BucketState()
{
    SetBuckets(bucket_init_state);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const int *buckets)
{
    SetBuckets(buckets);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const BucketState& state)
{
    SetBuckets((const int *)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);
}

BucketState& BucketState::operator=(const BucketState& state)
{
    SetBuckets((const int *)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);
    return *this;
}

bool BucketState::IsSameState(const BucketState& state) const
{
    for(int i = 0; i < BUCKETS_COUNT; ++i)
    {
        if(bucket_s[i] != state.bucket_s[i])
            return false;
    }

    return true;
}

bool BucketState::operator == (const BucketState& state)
{
    for(int i = 0; i < BUCKETS_COUNT; ++i)
    {
        if(bucket_s[i] != state.bucket_s[i])
            return false;
    }

    return true;
}

void BucketState::SetAction(int w, int f, int t)
{
    curAction.water = w;
    curAction.from  = f;
    curAction.to    = t;
}

void BucketState::SetBuckets(const int *buckets)
{
    for(int i = 0; i < BUCKETS_COUNT; ++i)
    {
        bucket_s[i] = buckets[i];
    }
}

bool BucketState::IsBucketEmpty(int bucket)
{
    Q_ASSERT((bucket >= 0) && (bucket < BUCKETS_COUNT));

    return (bucket_s[bucket] == 0);
}

bool BucketState::IsBucketFull(int bucket)
{
    Q_ASSERT((bucket >= 0) && (bucket < BUCKETS_COUNT));

    return (bucket_s[bucket] >= bucket_capicity[bucket]);
}

void BucketState::PrintStates()
{
    qDebug() << "Dump " << curAction.water << " water from "
         << curAction.from + 1 << " to " << curAction.to + 1 << ", ";
    qDebug() << "buckets water states is : ";

    for(int i = 0; i < BUCKETS_COUNT; ++i)
    {
        qDebug() << bucket_s[i] << " ";
    }
    qDebug() << endl;
}

bool BucketState::IsFinalState()
{
    return IsSameState(BucketState(bucket_final_state));
}

bool BucketState::CanTakeDumpAction(int from, int to)
{
    Q_ASSERT((from >= 0) && (from < BUCKETS_COUNT));
    Q_ASSERT((to >= 0) && (to < BUCKETS_COUNT));
    /*不是同一个桶，且from桶中有水，且to桶中不满*/

    if( (from != to)
        && !IsBucketEmpty(from)
        && !IsBucketFull(to) )
    {
        return true;
    }

    return false;
}

/*从from到to倒水，返回实际倒水体积*/
bool BucketState::DumpWater(int from, int to, BucketState& next)
{
    next.SetBuckets(bucket_s);     //当前3个桶中水量状态，赋值给下一个状态
    int dump_water = bucket_capicity[to] - bucket_s[to];   //当前状态下，要倒入的桶中有多少剩余空间
    if(next.bucket_s[from] >= dump_water)       //空间比来源桶中水少，就把目标桶倒满
    {
        next.bucket_s[to] += dump_water;      //也可以是next.bucket_s[to] = bucket_capicity[to];
        next.bucket_s[from] -= dump_water;
    }
    else
    {
        next.bucket_s[to] += next.bucket_s[from];
        dump_water = next.bucket_s[from];
        next.bucket_s[from] = 0;
    }
    if(dump_water > 0) /*是一个有效的倒水动作?*/
    {
        next.SetAction(dump_water, from, to);   //action中内容仅作为输出显示使用，与算法本身无关
        return true;
    }

    return false;
}


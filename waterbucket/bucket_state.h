#ifndef BUCKET_STATE
#define BUCKET_STATE


const int BUCKETS_COUNT = 3;

typedef struct tagACTION
{
    int from;
    int to;
    int water;
}ACTION;

class BucketState
{
public:
    BucketState();
    BucketState(const int *buckets);
    BucketState(const BucketState& state);
    BucketState& operator=(const BucketState& state);
    bool IsSameState(const BucketState& state) const;
    bool operator == (const BucketState& state);
    void SetAction(int w, int f, int t);
    void SetBuckets(const int *buckets);
    bool CanTakeDumpAction(int from, int to);
    bool IsBucketEmpty(int bucket);
    bool IsBucketFull(int bucket);
    void PrintStates();
    bool IsFinalState();
    bool DumpWater(int from, int to, BucketState& next);
public:
    int bucket_s[BUCKETS_COUNT];
    ACTION curAction;
};

#endif // BUCKET_STATE


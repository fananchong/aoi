#include <aoi.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

#include <chrono>


long long get_tick_count(void)
{
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;
    nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
    return tp.time_since_epoch().count();
}

#ifdef _DEBUG
#define myassert(X) assert(X)
#else
#define myassert(X) \
if (!(X))\
{\
   throw "error!";\
}
#endif

// Need to inherit aoi::Object
class A : public aoi::Object
{
public:
    A(float x, float y) : aoi::Object(x, y) {}

private:
};

typedef aoi::Scene<A, 16> SceneType;

void _test_add(SceneType& scn, std::vector<A*>& items)
{
    float x = float(rand() % int(scn.GetBounds().Right() - scn.GetBounds().Left())) + scn.GetBounds().Left();
    float y = float(rand() % int(scn.GetBounds().Top() - scn.GetBounds().Bottom())) + scn.GetBounds().Bottom();
    A* temp = new A(x, y);
    myassert(scn.Insert(temp));
    items.push_back(temp);
}

void _test_delete(SceneType& scn, std::vector<A*>& items, size_t count)
{
    size_t itemsNum = items.size();
    if (itemsNum == 0)
    {
        return;
    }
    std::random_shuffle(items.begin(), items.end());
    for (size_t i = 0; i < (std::min)(count, itemsNum); i++)
    {
        A* temp = items.back();
        myassert(scn.Remove(temp));
        delete(temp);
        items.pop_back();
    }
}

void _test_query(SceneType& scn, std::vector<A*>& items)
{
    unsigned testCount = 0;
    aoi::Rect queryArea = aoi::Rect(
        float(rand() % 10),
        float(rand() % int(scn.GetBounds().Right() - scn.GetBounds().Left())) + scn.GetBounds().Left(),
        float(rand() % 10),
        float(rand() % int(scn.GetBounds().Top() - scn.GetBounds().Bottom())) + scn.GetBounds().Bottom());

    for (size_t i = 0; i < items.size(); i++)
    {
        if (queryArea.Contains(items[i]))
        {
            testCount++;
        }
    }

    unsigned findCount = 0;
    aoi::Object* ptr = scn.Query(queryArea);
    while (ptr)
    {
        findCount++;
        ptr = ptr->Next();
    }
    //printf("find obj count:%u, test count:%u, total count:%u\n", findCount, testCount, scn.GetItemCount());
    myassert(testCount == findCount);
}

void _test_query(SceneType& scn, std::vector<A*>& items, float radius)
{
    unsigned testCount = 0;

    size_t index = rand() % items.size();
    aoi::Rect queryArea = aoi::Rect(
        items[index]->X - radius,
        items[index]->X + radius,
        items[index]->Y - radius,
        items[index]->Y + radius);

    for (size_t i = 0; i < items.size(); i++)
    {
        if (queryArea.Contains(items[i]))
        {
            testCount++;
        }
    }

    unsigned findCount = 0;
    aoi::Object* ptr = scn.Query(items[index], radius);
    while (ptr)
    {
        findCount++;
        ptr = ptr->Next();
    }
    //printf("find obj count:%u, test count:%u, total count:%u\n", findCount, testCount, scn.GetItemCount());
    myassert(testCount == findCount);
}


void test1()
{
    aoi::Rect rect(0, 1000, 0, 1000);
    SceneType scn(rect);

    // Test insertion
    std::vector<A*> items;
    for (size_t i = 0; i < 8192; i++)
    {
        _test_add(scn, items);
    }

    // Test query
    for (size_t i = 0; i < 1000; i++)
    {
        _test_query(scn, items);
        _test_query(scn, items, float(rand() % 200 + 50));
    }


    // Test delete
    unsigned itemsNum = items.size();
    _test_delete(scn, items, itemsNum);
    items.clear();
    //printf("delete obj count:%u, total count:%u\n", itemsNum, scn.GetItemCount());
}

void test2()
{
    aoi::Rect rect(0, 1000, 0, 1000);
    SceneType scn(rect);

    std::vector<A*> items;
    while (true)
    {
        unsigned op = rand() % 10;

        if (op <= 6)
        {
            _test_add(scn, items);
        }
        else if (op <= 8)
        {
            int itemsNum = (int)items.size();
            _test_delete(scn, items, itemsNum % 3 + 1);
        }
        else
        {
            _test_query(scn, items);
            _test_query(scn, items, float(rand() % 200 + 50));
        }
    }
}

void test3()
{
    unsigned w = 1000;
    unsigned h = 1000;
    float r = 0.6f;

    aoi::Rect rect(0, float(w), 0, float(h));
    SceneType scn(rect);


    size_t PLAYER_COUNT = 5000;
    size_t QUERYCOUNT = 10000;

    auto t1 = get_tick_count();
    for (size_t i = 0; i < PLAYER_COUNT; i++)
    {
        rand();
        rand();
    }
    auto t2 = get_tick_count();
    //printf("rand cost:%lldns %fns/op\n", t2 - t1, float(t2 - t1) / COUNT);
    long long ttr = t2 - t1;
    long long ttrop = (long long)(float(t2 - t1) / PLAYER_COUNT);

    printf("width:%u, heigth:%u\n", w, h);
    printf("player count: %u, query redius: %f\n", unsigned(PLAYER_COUNT), r);

    std::vector<A*> items;
    t1 = get_tick_count();
    for (size_t i = 0; i < PLAYER_COUNT; i++)
    {
        _test_add(scn, items);
    }
    t2 = get_tick_count();
    printf("insert cost:%12lldns %12.3fns/op\n", t2 - t1 - ttr, float(t2 - t1) / PLAYER_COUNT - ttrop);

    t1 = get_tick_count();
    for (size_t i = 0; i < QUERYCOUNT; i++)
    {
        for (size_t j = 0; j < PLAYER_COUNT; j++)
        {
            aoi::Rect rect(items[j]->X - r, items[j]->X + r, items[j]->Y - r, items[j]->Y + r);
            aoi::Object* ptr = scn.Query(items[j], float(r));
        }
    }
    t2 = get_tick_count();
    printf("query1 cost:%12lldns %12.3fns/op %12.3fms/op\n", t2 - t1, float(t2 - t1) / QUERYCOUNT, float(t2 - t1) / QUERYCOUNT / 1000000);

    t1 = get_tick_count();
    for (size_t i = 0; i < QUERYCOUNT; i++)
    {
        for (size_t j = 0; j < PLAYER_COUNT; j++)
        {
            aoi::Rect rect(items[j]->X - r, items[j]->X + r, items[j]->Y - r, items[j]->Y + r);
            aoi::Object* ptr = scn.Query(rect);
        }
    }
    t2 = get_tick_count();
    printf("query2 cost:%12lldns %12.3fns/op %12.3fms/op\n", t2 - t1, float(t2 - t1) / QUERYCOUNT, float(t2 - t1) / QUERYCOUNT / 1000000);
}

void test4()
{
    aoi::Rect rect(0, 1000, 0, 1000);
    SceneType scn(rect);
    for (size_t i = 0; i < 10000; i++)
    {
        float x = 0;
        float y = 0;
        A* temp = new A(x, y);
        myassert(scn.Insert(temp));
    }
}

int main()
{
    srand((unsigned)time(0));

    //test1();
    //test2();
    test3();
    //test4();
    return 0;
}

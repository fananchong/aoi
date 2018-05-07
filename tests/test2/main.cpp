#include <aoi.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

#ifdef _DEBUG
#define myassert(X) assert(X)
#else
#define myassert(X) \
if (!(X))\
{\
   throw "error!";\
}
#endif

// 需要继承 aoi::Object
class A : public aoi::Object, public aoi::Point
{
public:
    A(float x, float y) : aoi::Point(x, y) {}

    // 需要实现以下接口
    aoi::Point& GetPos() override { return *(aoi::Point*)this; }

private:
};

typedef aoi::Scene<A, 16> SceneType;

void _test_add(SceneType& scn, std::vector<A*>& items)
{
    float x = float(rand() % 1000);
    float y = float(rand() % 1000);
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
    for (size_t i = 0; i < std::min(count, itemsNum); i++)
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
        float(rand() % 100),
        float(rand() % 1000),
        float(rand() % 100),
        float(rand() % 1000));

    for (size_t i = 0; i < items.size(); i++)
    {
        auto& pos = items[i]->GetPos();
        if (queryArea.Contains(pos))
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


void test1()
{
    aoi::Rect rect(0, 1000, 0, 1000);
    SceneType scn(rect);

    // 测试插入
    std::vector<A*> items;
    for (size_t i = 0; i < 8192; i++)
    {
        _test_add(scn, items);
    }

    // 测试查询
    for (size_t i = 0; i < 1000; i++)
    {
        _test_query(scn, items);
    }


    // 测试删除
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
        }
    }
}

int main()
{
    srand((unsigned)time(0));

    test1();
    test2();

    return 0;
}
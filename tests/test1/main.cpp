#include <impl/alloc.h>
#include <aoi.h>
#include <stdlib.h>
#include <chrono>


long long get_tick_count(void)
{
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> microClock_type;
    microClock_type tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    return tp.time_since_epoch().count();
}

class A
{
public:
    A() :a1(0), b1(0)
    {
        //printf("call A()#1\n");
    }

    A(int a, float b) :a1(a), b1(b)
    {
        //printf("call A()#2\n");
    }

    ~A()
    {
        //printf("call ~A()\n");
    }
public:
    int a1;
    char c1;
    float b1;
    char d1[168];
};

typedef aoi::impl::QuadTreeNode<A, 16, 10> NodeType;

int main() {

    printf("sizeof(NodeType): %d\n", int(sizeof(NodeType)));
    aoi::impl::Mem<NodeType> mem;

    size_t COUNT = 10000000;

    auto t1 = get_tick_count();
    for (size_t i = 0; i < COUNT; i++)
    {
        auto temp = new NodeType(0, &mem, aoi::impl::NodeTypeLeaf, nullptr, aoi::Rect());
        delete temp;
    }
    auto t2 = get_tick_count();
    printf("new cost:%lld\n", t2 - t1);

    aoi::impl::Mem<NodeType> mem2;
    t1 = get_tick_count();
    for (size_t i = 0; i < COUNT; i++)
    {
        auto temp = mem2.New(0, &mem, aoi::impl::NodeTypeLeaf, nullptr, aoi::Rect());
        mem2.Delete(temp);
    }
    t2 = get_tick_count();
    printf("mem cost:%lld\n", t2 - t1);

    aoi::impl::AlignedMem<NodeType> mem3;
    t1 = get_tick_count();
    for (size_t i = 0; i < COUNT; i++)
    {
        auto temp = mem3.New(0, &mem, aoi::impl::NodeTypeLeaf, nullptr, aoi::Rect());
        mem3.Delete(temp);
    }
    t2 = get_tick_count();
    printf("aligned mem cost:%lld\n", t2 - t1);

    return 0;
}


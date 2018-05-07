#include <impl/alloc.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#elif defined(__GNUC__)
#include <sys/sysinfo.h>
#include <sys/time.h>
#endif

unsigned long get_tick_count(void)
{
    unsigned long current_time;
#ifdef _MSC_VER
    current_time = GetTickCount();
#else
    struct timeval current;
    gettimeofday(&current, NULL);
    current_time = current.tv_sec * 1000 + current.tv_usec / 1000;
#endif
    return current_time;
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
};

int main() {
    aoi::impl::Mem<A> mem;

    A* b = mem.New();
    mem.Delete(b);

    A* c = mem.New(1, 1.2f);
    mem.Delete(c);


#ifdef _MSC_VER
    size_t COUNT = 10000000;

    auto t1 = GetTickCount();
    for (size_t i = 0; i < COUNT; i++)
    {
        auto temp = new A(1, 2.0f);
        temp->a1 = int(temp->a1 + temp->b1 + temp->c1);
        delete temp;
    }
    auto t2 = GetTickCount();
    printf("new cost:%u\n", t2 - t1);

    aoi::impl::Mem<A> mem2;
    t1 = GetTickCount();
    for (size_t i = 0; i < COUNT; i++)
    {
        auto temp = mem2.New(1, 2.0f);
        temp->a1 = int(temp->a1 + temp->b1 + temp->c1);
        mem2.Delete(temp);
    }
    t2 = GetTickCount();
    printf("mem cost:%u\n", t2 - t1);

    aoi::impl::AlignedMem<A> mem3;
    t1 = GetTickCount();
    for (size_t i = 0; i < COUNT; i++)
    {
        auto temp = mem3.New(1, 2.0f);
        temp->a1 = int(temp->a1 + temp->b1 + temp->c1);
        mem3.Delete(temp);
    }
    t2 = GetTickCount();
    printf("aligned mem cost:%u\n", t2 - t1);

#endif

    return 0;
}
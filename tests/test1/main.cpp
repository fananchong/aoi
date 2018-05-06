#include <impl/alloc.h>
#include <stdlib.h>

class A
{
public:
    A()
    {
        printf("call A()#1\n");
    }

    A(int a, float b)
    {
        printf("call A()#2\n");
    }

    ~A()
    {
        printf("call ~A()\n");
    }
};

int main() {
    aoi::impl::Mem<A> mem;

    A* b = mem.New();
    mem.Delete(b);

    A* c = mem.New(1, 1.2f);
    mem.Delete(c);


    return 0;
}
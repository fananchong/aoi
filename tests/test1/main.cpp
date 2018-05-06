#include <impl/alloc.h>
#include <stdlib.h>

void* myAlloc(size_t size)
{
    printf("call myAlloc\n");
    return malloc(size);
}

void myFree(void* ptr)
{
    printf("call myFree\n");
    free(ptr);
}

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
    aoi::impl::Mem<int> mem;

    int* a = (int*)mem.Alloc(sizeof(int));
    *a = 1;
    mem.Free(a);

    aoi::impl::Mem<A> mem2;
    mem2.SetCustom(myAlloc, myFree);

    A* b = mem2.New();
    mem2.Delete(b);

    A* c = mem2.New(1, 1.2f);
    mem2.Delete(c);


    return 0;
}
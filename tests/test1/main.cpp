#include <impl/alloc.h>
#include <stdlib.h>

int* myNew()
{
    printf("call myNew\n");
    return new int();
}

void myDelete(int* ptr)
{
    printf("call myDelete\n");
    delete ptr;
}

int main() {
    aoi::impl::Alloc<int> alloc;

    int* a = alloc.New();
    *a = 1;
    alloc.Delete(a);

    alloc.SetCustom(myNew, myDelete);

    int* b = alloc.New();
    *b = 10;
    alloc.Delete(b);

    return 0;
}
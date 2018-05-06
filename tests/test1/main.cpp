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

int main() {
    aoi::impl::Mem<int> mem;

    int* a = (int*)mem.Alloc(sizeof(int));
    *a = 1;
    mem.Free(a);

    mem.SetCustom(myAlloc, myFree);

    int* b = (int*)mem.Alloc(sizeof(int));
    *b = 10;
    mem.Free(b);

    return 0;
}
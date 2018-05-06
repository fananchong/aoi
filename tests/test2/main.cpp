#include <impl/quadtree.h>
#include <stdlib.h>

class A : public aoi::impl::Point
{
public:
    A(float x, float y) : aoi::impl::Point(x, y) {}
    aoi::impl::Point& GetPos() { return *(aoi::impl::Point*)this; }
};

int main() {

    aoi::impl::QuadTree<A, 16> tree;

    A a(1, 2);
    tree.Insert(&a);

    return 0;
}
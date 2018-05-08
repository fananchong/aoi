#ifndef __AOI_SCENE_H__
#define __AOI_SCENE_H__

#include "point.h"
#include "impl/quadtree.h"

namespace aoi
{
    class Object : public Point
    {
    public:
        Object() : Point(), mNode(nullptr), mQueryNext(nullptr), mItemNext(nullptr) {}
        Object(float x, float y) : Point(x, y), mNode(nullptr), mQueryNext(nullptr), mItemNext(nullptr) {}
        virtual ~Object() {}

        inline Object* Next() { return mQueryNext; }

    private:
        void* mNode;
        Object* mQueryNext;
        void* mItemNext;

        template<typename TItem, unsigned NodeCapacity, typename TAlloc> friend class impl::QuadTree;
        template<typename TItem, unsigned NodeCapacity> friend class impl::QuadTreeNode;
    };

    template<typename TItem, unsigned NodeCapacity, typename TAlloc = impl::AlignedMem<impl::QuadTreeNode<TItem, NodeCapacity>>>
    using Scene = impl::QuadTree<TItem, NodeCapacity, TAlloc>;
}

#endif
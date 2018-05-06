#ifndef __AOI_IMPL_QUADTREE_H__
#define __AOI_IMPL_QUADTREE_H__

#include "alloc.h"
#include "quadtreenode.h"

namespace aoi
{
    namespace impl
    {

        template<typename TItem, unsigned ItemN>
        class QuadTree {
        public:



        private:
            Mem<QuadTreeNode<TItem, ItemN>> mRoot;
        };
    }
}

#endif

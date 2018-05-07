#ifndef __AOI_IMPL_QUADTREE_H__
#define __AOI_IMPL_QUADTREE_H__

#include "alloc.h"
#include "quadtreenode.h"

namespace aoi
{
    namespace impl
    {
        template<typename TItem, unsigned NodeCapacity, typename TAlloc = Mem<QuadTreeNode<TItem, NodeCapacity>>>
        class QuadTree {
        public:
            using TNode = QuadTreeNode<TItem, NodeCapacity>;

            QuadTree(const Rect& bounds) : mRoot(&mAlloc, NodeTypeLeaf, nullptr, bounds) {}
            ~QuadTree() {}

            bool Insert(TItem* item) { return mRoot.Insert(item); }

            bool Remove(TItem* item)
            {
                TNode* node = (TNode*)item->mNode;
                return node ? node->Remove(item) : false;
            }

            TItem* Query(const Rect& area)
            {
                TItem* head = nullptr;
                TItem* tail = nullptr;
                mRoot.Query(area, head, tail);
                tail ? tail->mNext = nullptr : 0;
                return head;
            }

            unsigned GetItemCount() { return mRoot.GetItemCount(); }

        private:
            Rect mBounds;        // 节点边框范围
            TAlloc mAlloc;       // 节点分配器
            TNode mRoot;         // 根节点
        };
    }
}

#endif

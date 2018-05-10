#ifndef __AOI_IMPL_QUADTREENODE_H__
#define __AOI_IMPL_QUADTREENODE_H__

#include "alloc.h"
#include "../rect.h"
#include <memory>

namespace aoi
{
    namespace impl
    {
        enum ENodeType
        {
            NodeTypeNormal = 0,  // 非叶节点
            NodeTypeLeaf = 1,    // 叶子节点
        };

        const unsigned ChildrenNum = 4;

        template<typename TItem, unsigned NodeCapacity, unsigned LevelLimit>
        class QuadTreeNode
        {
        public:
            using TNode = QuadTreeNode<TItem, NodeCapacity, LevelLimit>;

            QuadTreeNode(unsigned level, MemBase<TNode>* alloc, ENodeType type, QuadTreeNode* parent, const Rect& bounds);
            ~QuadTreeNode();

            bool Insert(TItem* item);
            bool Remove(TItem* item);
            void Query(const Rect& area, TItem*& head, TItem*& tail);
            unsigned GetItemCount();

        public:
            unsigned mLevel;                         // 当前节点所在层级
            Rect mBounds;                            // 节点边框范围
            QuadTreeNode* mParent;                   // 父节点
            ENodeType mNodeType;                     // 节点类型
            QuadTreeNode* mChildrens[ChildrenNum];   // 孩子节点
            unsigned mItemCount;                     // 叶子节点上的Item数量
            TItem* mItems;                           // 叶子节点上的Items

        private:
            MemBase<TNode>* mAlloc;                  // 节点分配器
            void split();
            void tryMerge();
        };
    }
}

#include "quadtreenode_impl.h"

#endif

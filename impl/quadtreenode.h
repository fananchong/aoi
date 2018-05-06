#ifndef __AOI_IMPL_QUADTREENODE_H__
#define __AOI_IMPL_QUADTREENODE_H__

#include "rect.h"
#include <memory>

namespace aoi
{
    namespace impl
    {
        enum NodeType
        {
            NodeTypeNormal = 0,  // 非叶节点
            NodeTypeLeaf = 1,    // 叶子节点
        };

        template<typename TItem, unsigned ItemN>
        class QuadTreeNode
        {
        public:
            QuadTreeNode();
            ~QuadTreeNode();

            void Reset();
            bool Insert(TItem* item);

        public:
            Rect mBounds;                      // 节点边框范围
            QuadTreeNode* mParent;             // 父节点
            NodeType mNodeType;                // 节点类型
            union
            {
                QuadTreeNode* mChildrens[4];   // 孩子节点
                struct
                {
                    unsigned mItemCount;       // 叶子节点上的Item数量
                    TItem* mItems[ItemN];      // 叶子节点上的Items
                };
            }mContent;
            
            // TODO: 邻居信息
        };
    }
}

#include "quadtreenode_impl.h"

#endif

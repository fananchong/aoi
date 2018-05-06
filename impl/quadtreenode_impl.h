#include "point.h"
#include <cassert>

namespace aoi
{
    namespace impl
    {
        template<typename TItem, unsigned ItemN>
        QuadTreeNode<TItem, ItemN>::QuadTreeNode(Mem<TNode>& alloc, ENodeType type, QuadTreeNode* parent)
            : mAlloc(alloc)
            , mParent(parent)
            , mNodeType(type)
            , mItemCount(0)
        {
            memset(mChildrens, 0, sizeof(mChildrens));
        }

        template<typename TItem, unsigned ItemN>
        QuadTreeNode<TItem, ItemN>::~QuadTreeNode()
        {

        }

        template<typename TItem, unsigned ItemN>
        void QuadTreeNode<TItem, ItemN>::Reset()
        {
            mBounds.Reset();
            mParent = nullptr;
            mNodeType = NodeTypeNormal;
            mItemCount = 0;
            memset(mChildrens, 0, sizeof(mChildrens));
        }

        template<typename TItem, unsigned ItemN>
        bool QuadTreeNode<TItem, ItemN>::Insert(TItem* item)
        {
            Point& pos = item->GetPos();

            if (mNodeType == NodeTypeNormal)
            {
            LABLE_NORMAL:
                int index = mBounds.GetQuadrant(pos) - 1;
                return index >= 0 ? mChildrens[index]->Insert(item) : false;
            }
            else
            {
                if (mItemCount < ItemN)
                {
                    return mBounds.Contains(pos) ? (mItems[mItemCount++] = item, true) : false;
                }
                else
                {
                    createChildrens();
                    goto LABLE_NORMAL;
                }
            }
        }

        template<typename TItem, unsigned ItemN>
        void QuadTreeNode<TItem, ItemN>::createChildrens()
        {
            mNodeType = NodeTypeNormal;

            for (size_t i = 0; i < sizeof(mChildrens) / sizeof(mChildrens[0]); i++)
            {
                mChildrens[i] = mAlloc.New(mAlloc, NodeTypeLeaf, this);
            }

            // 第一象限，右上
            mChildrens[0]->mBounds.Reset(mBounds.MidX(), mBounds.Top(), mBounds.Right(), mBounds.MidY());

            // 第二象限，左上
            mChildrens[1]->mBounds.Reset(mBounds.Left(), mBounds.Top(), mBounds.MidX(), mBounds.MidY());

            // 第三象限，左下
            mChildrens[2]->mBounds.Reset(mBounds.Left(), mBounds.MidY(), mBounds.MidX(), mBounds.Bottom());

            // 第四象限，右下
            mChildrens[3]->mBounds.Reset(mBounds.MidX(), mBounds.MidY(), mBounds.Right(), mBounds.Bottom());

            for (size_t i = 0; i < mItemCount; i++)
            {
                Point& pos = mItems[i]->GetPos();
                int index = mBounds.GetQuadrant2(pos) - 1;
                mChildrens[index]->Insert(mItems[i]);
            }
            mItemCount = 0;
        }
    }
}
#include "point.h"

namespace aoi
{
    namespace impl
    {
        template<typename TItem, unsigned ItemN>
        QuadTreeNode<TItem, ItemN>::QuadTreeNode()
            : mParent(nullptr)
            , mNodeType(NodeTypeNormal)
            , mItemCount(0)
        {
        }

        template<typename TItem, unsigned ItemN>
        QuadTreeNode<TItem, ItemN>::~QuadTreeNode()
        {

        }

        template<typename TItem, unsigned ItemN>
        void QuadTreeNode<TItem, ItemN>::Reset()
        {
            mBounds.Reset()
            mParent = nullptr;
            mNodeType = NodeTypeNormal;
            mItemCount = 0;
        }

        template<typename TItem, unsigned ItemN>
        bool QuadTreeNode<TItem, ItemN>::Insert(TItem* item)
        {
            Point& pos = item->GetPos();
            if (!mBound.Contains(pos))
            {
                return false;
            }

            if (mNodeType == NodeTypeLeaf)
            {
                if (mItemCount < ItemN)
                {
                    mItems[mItemCount++] = item;
                }
                else
                {
                    // TODO: ╥жая
                }
            }
            else
            {
                for (size_t i = 0; i < sizeof(mChildrens) / sizeof(mChildrens[0]); i++)
                {
                    if (mChildrens[i] && mChildrens[i].GetBound().Contains(pos))
                    {
                        mChildrens[i]->Insert(item);
                        break;
                    }
                }
            }
        }
    }
}
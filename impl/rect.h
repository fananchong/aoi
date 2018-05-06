#ifndef __AOI_IMPL_RECT_H__
#define __AOI_IMPL_RECT_H__

#include "point.h"

namespace aoi
{
    namespace impl
    {
        class Rect
        {
        public:

            Rect() : mLeft(0), mRight(0), mTop(0), mBottom(0), mWidth(0), mHeight(0) { }

            Rect(float left, float top, float right, float bottom)
                : mLeft(left)
                , mRight(right)
                , mTop(top)
                , mBottom(bottom)
                , mWidth(right - left)
                , mHeight(top - bottom)
            {
            }

            Rect(const Rect& other)
                : mLeft(other.mLeft)
                , mRight(other.mRight)
                , mTop(other.mTop)
                , mBottom(other.mBottom)
                , mWidth(other.mRight - other.mLeft)
                , mHeight(other.mTop - other.mBottom)
            {
            }

            Rect(Point center, Size halfExtents)
                : mLeft(center.X - halfExtents.X)
                , mRight(center.X + halfExtents.X)
                , mTop(center.Y + halfExtents.Y)
                , mBottom(center.Y - halfExtents.Y)
                , mWidth(mRight - mLeft)
                , mHeight(mTop - mBottom)
            {
            }

            inline void Reset()
            {
                mLeft = 0;
                mRight = 0;
                mTop = 0;
                mBottom = 0;
                mWidth = 0;
                mHeight = 0;
            }

            inline float Left() const { return mLeft; }
            inline float Right() const { return mRight; }
            inline float Bottom() const { return mBottom; }
            inline float Top() const { return mTop; }
            inline float MidX() const { return mLeft + mWidth / 2; }
            inline float MidY() const { return mBottom + mHeight / 2; }

            inline bool Empty() const { return mWidth == 0 && mHeight == 0; }

            inline bool Contains(const Rect& Rect) const
            {
                return (mLeft <= Rect.mLeft
                    && mBottom <= Rect.mBottom
                    && Rect.mRight <= mRight
                    && Rect.mTop <= mTop);
            }

            inline bool Contains(float x, float y) const
            {
                return (x >= mLeft && x <= mRight
                    && y >= mBottom && y <= mTop);
            }

            inline bool Contains(const Point& point) const
            {
                return Contains(point.X, point.Y);
            }

            inline bool Intersects(const Rect& Rect) const
            {
                return !(mRight < mLeft
                    || Rect.mRight < mLeft
                    || mTop < Rect.mBottom
                    || Rect.mTop < mBottom);
            }

        private:
            float mLeft;
            float mRight;
            float mTop;
            float mBottom;
            float mWidth;
            float mHeight;
        };
    }
}

#endif

#ifndef __AOI_IMPL_ALLOC_H__
#define __AOI_IMPL_ALLOC_H__

#include <functional>
#include <cassert>

namespace aoi
{
    namespace impl
    {
        template<typename T>
        class MemBase
        {
        public:
            MemBase() {}
            virtual ~MemBase() {}

            virtual void* _alloc(size_t size) = 0;
            virtual void _free(void* ptr) = 0;

            template<typename ... Args>
            inline T* New(Args... args)
            {
                void *ptr = _alloc(sizeof(T));
                return new (ptr)T(args...);
            }
            inline void Delete(T* ptr)
            {
                ptr->~T();
                _free(ptr);
            }
        };

        template<typename T, unsigned BlockSize = 4096>
        class Mem : public MemBase<T>
        {
        public:
            Mem()
                : mBlocks(nullptr)
                , mHead(nullptr)
            {
            }

            ~Mem()
            {
                while (mBlocks)
                {
                    Item* next = mBlocks->next;
                    free(mBlocks);
                    mBlocks = next;
                }
            }

            void* _alloc(size_t size) override
            {
                if (!mHead)
                {
                    newBlock();
                }
                void* ptr = mHead;
                mHead = mHead->next;
                return ptr;
            }

            void _free(void* ptr) override
            {
                Item* p = (Item*)ptr;
                p->next = mHead;
                mHead = p;
            }

        private:
            void newBlock()
            {
                assert(!mHead);
                Item* ptr = (Item*)malloc(BlockSize);
                if (mBlocks)
                {
                    ptr->next = mBlocks;
                    mBlocks = ptr;
                }
                else
                {
                    mBlocks = ptr;
                    mBlocks->next = 0;
                }

#define MYITEMPTR(N) ((Item*)((char*)ptr + (N) * sizeof(T)))

                mHead = MYITEMPTR(1);
                size_t lst = BlockSize / sizeof(T) - 1;
                for (size_t i = 1; i < lst; i++)
                {
                    MYITEMPTR(i)->next = MYITEMPTR(i + 1);
                }
                MYITEMPTR(lst)->next = nullptr;
            }

            struct Item
            {
                Item* next;
            };
            Item* mBlocks;
            Item* mHead;
        };
    }
}

#endif
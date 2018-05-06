#ifndef __AOI_IMPL_ALLOC_H__
#define __AOI_IMPL_ALLOC_H__

#include <functional>
#include <list>

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


        // TODO: 暂时随便实现下，类接口等跑通
        template<typename T>
        class Mem : public MemBase<T>
        {
        public:
            Mem() {}
            ~Mem()
            {
                for (auto it = mHolds.begin(); it != mHolds.end(); it++)
                {
                    free(*it);
                }
                mHolds.clear();
            }

            void* _alloc(size_t size) override
            {
                void* ptr = malloc(size);
                mHolds.push_back(ptr);
                return ptr;
            }

            void _free(void* ptr) override
            {
                // do nothing
            }
        private:
            std::list<void*> mHolds;
        };
    }
}

#endif
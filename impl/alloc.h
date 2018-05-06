#ifndef __AOI_IMPL_ALLOC_H__
#define __AOI_IMPL_ALLOC_H__

#include <functional>

namespace aoi
{
    namespace impl
    {

        typedef std::function<void*(size_t size)> AllocType;
        typedef std::function<void(void*)> FreeType;
        typedef std::function<void(void)> ReleaseType;

        inline void* defaultAlloc(size_t size) { return malloc(size); }
        inline void defaultFree(void* ptr) { free(ptr); }

        template<class T>
        class Mem
        {
        public:
            Mem() : mAlloc(defaultAlloc), mFree(defaultFree), mRelease(nullptr) { }
            Mem(const AllocType& f1, const FreeType& f2, const ReleaseType& f3 = nullptr) : mAlloc(f1), mFree(f2), mRelease(f3) { }
            ~Mem() { if (mRelease) { mRelease(); } }

            inline void* Alloc(size_t size) { return mAlloc(size); }
            inline void Free(void* ptr) { mFree(ptr); }

            template<class ... Args>
            inline T* New(Args... args)
            {
                void *ptr = mAlloc(sizeof(T));
                return new (ptr)T(args...);
            }
            inline void Delete(T* ptr)
            {
                ptr->~T();
                mFree(ptr);
            }

        protected:
            AllocType mAlloc;
            FreeType mFree;
            ReleaseType mRelease;
        };

    }
}

#endif
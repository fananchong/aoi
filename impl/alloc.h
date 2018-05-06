#ifndef __AOI_IMPL_ALLOC_H__
#define __AOI_IMPL_ALLOC_H__

#include <functional>

namespace aoi
{
    namespace impl
    {
        template<class T>
        class Mem
        {
        public:
            typedef std::function<void*(size_t size)> AllocType;
            typedef std::function<void(void*)> FreeType;

            static void* Alloc(size_t size) { return sAlloc(size); }
            static void Free(void* ptr) { sFree(ptr); }
            static void SetCustom(const AllocType& f1, const FreeType& f2) { sAlloc = f1;sFree = f2; }

        private:
            static void* defaultAlloc(size_t size) { return malloc(size); }
            static void defaultFree(void* ptr) { delete ptr; }

            static AllocType sAlloc;
            static FreeType sFree;
        };

        template<class T> typename Mem<T>::AllocType Mem<T>::sAlloc = Mem<T>::defaultAlloc;
        template<class T> typename Mem<T>::FreeType Mem<T>::sFree = Mem<T>::defaultFree;
    }
}

#endif
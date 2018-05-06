#ifndef __AOI_IMPL_ALLOC_H__
#define __AOI_IMPL_ALLOC_H__

#include <functional>

namespace aoi
{
    namespace impl
    {
        template<class T>
        class Alloc
        {
        public:
            typedef std::function<T*()> NewHandlerType;
            typedef std::function<void(T*)> DeleteHandlerType;

            static T* New() { return sNewFunc(); }
            static void Delete(T* ptr) { sDeleteFunc(ptr); }
            static void SetCustom(const NewHandlerType& f1, const DeleteHandlerType& f2) { sNewFunc = f1;sDeleteFunc = f2; }

        private:
            static T* defaultNew() { return new T(); }
            static void defaultDelete(T* ptr) { delete ptr; }

            static NewHandlerType sNewFunc;
            static DeleteHandlerType sDeleteFunc;
        };

        template<class T> typename Alloc<T>::NewHandlerType Alloc<T>::sNewFunc = Alloc<T>::defaultNew;
        template<class T> typename Alloc<T>::DeleteHandlerType Alloc<T>::sDeleteFunc = Alloc<T>::defaultDelete;
    }
}

#endif
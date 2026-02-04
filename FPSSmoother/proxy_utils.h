#include <combaseapi.h>
#include "Proxies/ICloneable.h"

bool QueryProxy(REFIID riid, void **ppvObject);

template <typename T>
void QueryProxy(REFIID riid, void **ppvObject, T *proxy)
{
    if (QueryProxy(riid, ppvObject))
    {
        auto src = dynamic_cast<ICloneable<T> *>(proxy);
        auto dst = dynamic_cast<T *>(static_cast<IUnknown *>(*ppvObject));
        if (src && dst)
            src->CopyTo(dst);
    }
}

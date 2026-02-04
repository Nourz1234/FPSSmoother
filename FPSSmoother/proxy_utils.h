#include <combaseapi.h>
#include "Proxies/ICloneable.h"

bool QueryProxy(REFIID riid, void **ppvObject);

template <typename T>
void QueryProxy(REFIID riid, void **ppvObject, T *proxy)
{
    if (!QueryProxy(riid, ppvObject))
        return;

    auto src = dynamic_cast<ICloneable<T> *>(proxy);
    if (!src)
        return;

    auto dst = dynamic_cast<T *>(static_cast<IUnknown *>(*ppvObject));
    if (!dst)
        return;

    src->CopyTo(dst);
}

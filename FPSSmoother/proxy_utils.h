#include <combaseapi.h>
#include "Proxies/ProxyBase.h"

bool QueryProxy(REFIID riid, void **ppvObject);

template <typename T>
void QueryProxy(REFIID riid, void **ppvObject, T *proxy)
{
    if (QueryProxy(riid, ppvObject))
        proxy->CopyTo(static_cast<T *>(*ppvObject));
}

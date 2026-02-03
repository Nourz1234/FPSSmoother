#include <combaseapi.h>
#include "Proxies/ProxyBase.h"

bool QueryProxy(REFIID riid, void **ppvObject);
void QueryProxy(REFIID riid, void **ppvObject, ProxyBase *proxy);

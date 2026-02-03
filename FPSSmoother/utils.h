#pragma once
#include "globals.h"

#include <stdio.h>
#include <string>
#include <Windows.h>

#ifdef DEBUG

#include <typeinfo>

LPCSTR GetMB(LPCWSTR wc);
LPCWSTR GetWC(LPCSTR c);

LPCWSTR SwapChainSwapEffectToStr(DXGI_SWAP_EFFECT SwapEffect);
LPCWSTR SwapChainFlagsToStr(UINT Flags);

void fdebug(std::wstring str);

void debug(const wchar_t *_Format, ...);

class DbgLevel
{
public:
    DbgLevel() { g_DbgLevel += 1; }
    ~DbgLevel() { g_DbgLevel -= 1; }
};

#define inc_dbg_level(msg, ...)            \
    debug(msg __VA_OPT__(, ) __VA_ARGS__); \
    DbgLevel ll

#else

#define debug(...)
#define inc_dbg_level(...)

#endif

// i don't love it but it will have to do for now.
template <typename TProxy, typename T>
T *GetProxyFor(T *instance)
{
    if (g_StahpBruh)
    {
        debug(L"-> Stahp!");
        return instance;
    }

    TProxy *proxy = nullptr;
    HRESULT hr = instance->QueryInterface(IID_GetSelf, (void **)&proxy);
    if (SUCCEEDED(hr))
    {
        debug(L"-> Self");
        return proxy;
    }

    if (g_NumProxies >= 5000)
    {
        debug(L"-> Warning: Exceeded max proxy objects!");
        return instance;
    }
    g_NumProxies++;

    debug(L"-> %s", GetWC(typeid(T).name()));
    return static_cast<T *>(new TProxy(instance));
}

class ProxyHelper
{
    bool _proxyAttained = false;

public:
    template <typename TProxy, typename T>
    __inline void TryGetProxyForThisInterfaceForMePwease(REFIID riid, void **ppvObject)
    {
        if (_proxyAttained)
            return;
        if (IsEqualIID(riid, __uuidof(T)))
        {
            *ppvObject = GetProxyFor<TProxy>((T *)*ppvObject);
            _proxyAttained = true;
        }
    }

    __inline void AndThankYou(REFIID riid, void **ppvObject)
    {
        if (!_proxyAttained)
        {
            LPOLESTR pIID = 0;
            StringFromCLSID(riid, &pIID);
            debug(L"-> [ProxyHelper] Sowwy not found: %s", pIID);
        }
    }

    __inline bool UwU() { return _proxyAttained; }
};

FARPROC GetProcAddress2(LPCSTR dllName, LPCSTR funcName);

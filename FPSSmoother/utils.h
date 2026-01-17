#pragma once
#include "globals.h"

#include <stdio.h>
#include <string>
#include <Windows.h>

#ifdef DEBUG_BUILD

#include <typeinfo>

const char *GetMB(const wchar_t *wc);
const wchar_t *GetWC(const char *c);

void fdebug(std::wstring str);

template <typename... Args>
void debug(const wchar_t *_Format, Args... args)
{
    WCHAR buff[1024];
    swprintf_s(buff, _Format, args...);

    std::wstring str = L"";
    for (int i = 0; i < g_DbgLevel; ++i)
    {
        str.append(L"  ");
    }
    str.append(buff);
    str.append(L"\n");
    wprintf_s(str.c_str());

    fdebug(str);
}

__inline LPCWSTR SwapChainSwapEffectToStr(DXGI_SWAP_EFFECT SwapEffect)
{
    static wchar_t lpStr[1024]{};

    if (SwapEffect == DXGI_SWAP_EFFECT_DISCARD)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_DISCARD");
    if (SwapEffect == DXGI_SWAP_EFFECT_SEQUENTIAL)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_SEQUENTIAL");
    if (SwapEffect == DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL");
    if (SwapEffect == DXGI_SWAP_EFFECT_FLIP_DISCARD)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_FLIP_DISCARD");

    return lpStr;
}
__inline LPCWSTR SwapChainFlagsToStr(UINT Flags)
{
    std::wstring str = L"";

    if (Flags & DXGI_SWAP_CHAIN_FLAG_NONPREROTATED)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_NONPREROTATED ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_NONPREROTATED)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_NONPREROTATED ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS ");

    static wchar_t lpStr[1024]{};
    swprintf_s(lpStr, str.c_str());
    return lpStr;
}

class DbgLevel
{
public:
    DbgLevel() { g_DbgLevel += 1; }
    ~DbgLevel() { g_DbgLevel -= 1; }
};

#define inc_dbg_level(msg) \
    debug(msg);            \
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
#include <Windows.h>
#include <dxgi1_6.h>

#include "FPSSmoother/utils.h"
#include "FPSSmoother/proxy_utils.h"

#define DXGI_DLL_PATH "C:\\Windows\\System32\\dxgi.dll"

size_t g_CchAppCompatString = 0;
char g_AppCompatString[_MAX_ENV]{};

typedef void WINAPI SetAppCompatStringPointerProc(size_t cchString, const char *pszString);

EXTERN_C void WINAPI SetAppCompatStringPointer(size_t cchString, const char *pszString)
{
    // within this function we don't have access to shit.
    // calling any code outside of this dll (even the standard library and even the "new" operator!)
    // will cause an access violation.
    // apparently the system calls this before loading/initializing any dlls.

    g_CchAppCompatString = cchString;
    for (int i = 0; i < cchString; ++i)
    {
        g_AppCompatString[i] = pszString[i];
    }
    return;
}

typedef HRESULT WINAPI CreateDXGIFactoryProc(REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory(REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory");

    static CreateDXGIFactoryProc *RealCreateDXGIFactory = (CreateDXGIFactoryProc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory");

    HRESULT hr = RealCreateDXGIFactory(riid, ppFactory);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppFactory);
    }
    return hr;
}

typedef HRESULT WINAPI CreateDXGIFactory1Proc(REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory1");

    static CreateDXGIFactory1Proc *RealCreateDXGIFactory1 = (CreateDXGIFactory1Proc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory1");

    HRESULT hr = RealCreateDXGIFactory1(riid, ppFactory);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppFactory);
    }
    return hr;
}

typedef HRESULT WINAPI CreateDXGIFactory2Proc(UINT Flags, REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory2");

    static CreateDXGIFactory2Proc *RealCreateDXGIFactory2 = (CreateDXGIFactory2Proc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory2");

    HRESULT hr = RealCreateDXGIFactory2(Flags, riid, ppFactory);
    if (SUCCEEDED(hr))
    {
        // the only valid flag in the docs is DXGI_CREATE_FACTORY_DEBUG
        // anything else indicates an internal system call
        if ((Flags & ~DXGI_CREATE_FACTORY_DEBUG) != 0)
        {
            debug(L"-> Internal system call. Ignoring.");
        }
        else
        {
            QueryProxy(riid, ppFactory);
        }
    }
    return hr;
}

typedef HRESULT WINAPI DXGIGetDebugInterface1Proc(UINT Flags, REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI DXGIGetDebugInterface1(UINT Flags, REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"DXGIGetDebugInterface1");

    static DXGIGetDebugInterface1Proc *RealDXGIGetDebugInterface1 = (DXGIGetDebugInterface1Proc *)GetProcAddress2(DXGI_DLL_PATH, "DXGIGetDebugInterface1");

    return RealDXGIGetDebugInterface1(Flags, riid, ppFactory);
}

void DXGIMain()
{
    // this is important as without this, compatibility options are not passed to the app!
    // eg. "Disable fullscreen optimizations" (and possibly other compatibility options) won't work.
    // SetAppCompatStringPointer is called before the dll is even loaded somehow?!?!? (WTF?)
    // it gets called before DllMain and before anything is loaded really, so the handling for it is a bit special.
    // the hooked function just saves the string passed to it and then it is passed to the real function here.
    std::string compatString;
    if (g_CchAppCompatString)
    {
        compatString.append(g_AppCompatString, g_CchAppCompatString - 1);
    }
    if (g_SetFullscreenMode && g_FullscreenMode)
    {
        if (compatString.size() > 0)
            compatString.append(";");
        compatString.append("DisableMaximizedWindowedFullscreen=1;DisableMaximizedWindowedUpgrades=1");
    }

    if (compatString.size() > 0)
    {
        g_CchAppCompatString = compatString.size() + 1;
        strcpy_s(g_AppCompatString, compatString.c_str());

        SetAppCompatStringPointerProc *RealSetAppCompatStringPointer = (SetAppCompatStringPointerProc *)GetProcAddress2(DXGI_DLL_PATH, "SetAppCompatStringPointer");
        RealSetAppCompatStringPointer(g_CchAppCompatString, g_AppCompatString);
    }

    // {
    //     static char test[] = "ForceWARP=0;DisableMaximizedWindowedFullscreen=1;DisableMaximizedWindowedUpgrades=1;Hybrid=0;LowVidMemCap=0;EnableGraphicsPerfMonitor=0;DisableVrrSyncIntervalOverride=1";
    //     RealSetAppCompatStringPointer(sizeof(test), test);
    // }
}
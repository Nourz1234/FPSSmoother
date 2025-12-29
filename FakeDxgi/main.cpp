#include "FPSSmoother/DXGIAdapterProxy.h"
#include "FPSSmoother/DXGIFactoryProxy.h"
#include "FPSSmoother/DXGISwapChainProxy.h"
#include "FPSSmoother/D3D11DeviceProxy.h"
#include "FPSSmoother/Util.h"
#include "PatchJmp/PatchJmp.h"

#include <d3d11.h>
#include <Windows.h>
#include <pathcch.h>
#include <stdexcept>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Pathcch.lib")

#define DXGI_DLL_PATH "C:\\Windows\\System32\\dxgi.dll"

FARPROC GetProcAddress2(LPCSTR dllName, LPCSTR funcName)
{
    HMODULE hMod = GetModuleHandleA(dllName);
    if (!hMod)
    {
        hMod = LoadLibraryA(dllName);
    }
    return GetProcAddress(hMod, funcName);
}

size_t g_CchAppCompatString = 0;
char g_AppCompatString[_MAX_ENV];

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
    if (SUCCEEDED(hr) && g_DXGIHooking)
    {
        // we want to ensure that we have the correct riid because the system can pass in other values
        if (IsEqualIID(riid, __uuidof(IDXGIFactory)))
        {
            *ppFactory = GetProxyFor<DXGIFactoryProxy>((IDXGIFactory *)*ppFactory);
        }
        else
        {
            debug(L"-> Internal system call. Ignoring.");
        }
    }
    return hr;
}

typedef HRESULT WINAPI CreateDXGIFactory1Proc(REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory1");

    static CreateDXGIFactory1Proc *RealCreateDXGIFactory1 = (CreateDXGIFactory1Proc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory1");

    HRESULT hr = RealCreateDXGIFactory1(riid, ppFactory);
    if (SUCCEEDED(hr) && g_DXGIHooking)
    {
        IDXGIFactory *pTempFactory = GetProxyFor<DXGIFactoryProxy>((IDXGIFactory1 *)*ppFactory);
        hr = pTempFactory->QueryInterface(riid, ppFactory);
    }
    return hr;
}

typedef HRESULT WINAPI CreateDXGIFactory2Proc(UINT Flags, REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory2");

    static CreateDXGIFactory2Proc *RealCreateDXGIFactory2 = (CreateDXGIFactory2Proc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory2");

    HRESULT hr = RealCreateDXGIFactory2(Flags, riid, ppFactory);

    if (SUCCEEDED(hr) && g_DXGIHooking)
    {
        // the only valid flag in the docs is DXGI_CREATE_FACTORY_DEBUG
        // anything else indicates an internal system call
        if ((Flags & ~DXGI_CREATE_FACTORY_DEBUG) != 0)
        {
            debug(L"-> Internal system call. Ignoring.");
        }
        else
        {
            IDXGIFactory *pTempFactory = GetProxyFor<DXGIFactoryProxy>((IDXGIFactory2 *)*ppFactory);
            hr = pTempFactory->QueryInterface(riid, ppFactory);
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

// d3d12 patching

// undo_patch *g_D3D12CreateDevice_UndoPatch;

// HRESULT WINAPI FakeD3D12CreateDevice(
//     _In_opt_ IUnknown *pAdapter,
//     D3D_FEATURE_LEVEL MinimumFeatureLevel,
//     _In_ REFIID riid, // Expected: ID3D12Device
//     _COM_Outptr_opt_ void **ppDevice)
// {
//     inc_dbg_level(L"FakeD3D12CreateDevice");
//     debug(L"D3D12CreateDevice");

//     UndoPatch(g_D3D12CreateDevice_UndoPatch);

//     HRESULT hr = D3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
//     if (SUCCEEDED(hr))
//     {
//         *ppDevice = D3D11DeviceProxy::GetProxyFor(*ppDevice);
//     }

//     g_D3D12CreateDevice_UndoPatch = PatchAddress(D3D12CreateDevice, FakeD3D12CreateDevice);
//     return hr;
// }

#define ReadIniValue(ValueName)  \
    std::wstring s##ValueName;   \
    do                           \
    {                            \
        WCHAR buff[512]{};       \
        GetPrivateProfileString( \
            L"Preferences",      \
            L## #ValueName,      \
            NULL,                \
            buff,                \
            ARRAYSIZE(buff),     \
            iniPath);            \
        s##ValueName = buff;     \
    } while (false)

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
#ifdef DEBUG_BUILD
        AllocConsole();
        FILE *oldStream = NULL;
        freopen_s(&oldStream, "CONOUT$", "w", stdout);
#endif

        WCHAR iniPath[512];
        GetModuleFileName(hinstDLL, iniPath, ARRAYSIZE(iniPath));
        PathCchRemoveFileSpec(iniPath, ARRAYSIZE(iniPath));
        PathCchAppend(iniPath, ARRAYSIZE(iniPath), L"dxgi_preferences.ini");

        ReadIniValue(VSyncMode);
        ReadIniValue(PreferredRefreshRate);
        ReadIniValue(SwapChainBufferCount);
        ReadIniValue(SwapEffect);
        ReadIniValue(MaximumFrameLatency);
        ReadIniValue(AllowTearing);
        ReadIniValue(FPSLimit);

        ReadIniValue(DXGIHooking);
        ReadIniValue(D3D11Hooking);

        if (lstrcmpi(sVSyncMode.c_str(), L"Off") == 0)
        {
            g_SetSyncInterval = true;
            g_SyncInterval = 0;
            debug(L"VSyncMode: Off");
        }
        else if (lstrcmpi(sVSyncMode.c_str(), L"On") == 0)
        {
            g_SetSyncInterval = true;
            g_SyncInterval = 1;
            debug(L"VSyncMode: On");
        }
        else if (lstrcmpi(sVSyncMode.c_str(), L"OnHalfRefreshRate") == 0)
        {
            g_SetSyncInterval = true;
            g_SyncInterval = 2;
            debug(L"VSyncMode: OnHalfRefreshRate");
        }
        else
        {
            g_SetSyncInterval = false;
            debug(L"VSyncMode: Default");
        }

        if (lstrcmpi(sPreferredRefreshRate.c_str(), L"Default") == 0)
        {
            g_SetPreferredRefreshRate = false;
            debug(L"PreferredRefreshRate: Default");
        }
        else
        {
            try
            {
                g_PreferredRefreshRate = std::stoi(sPreferredRefreshRate);
                g_SetPreferredRefreshRate = true;
                debug(L"PreferredRefreshRate: %d", g_PreferredRefreshRate);
            }
            catch (std::invalid_argument)
            {
                g_SetPreferredRefreshRate = false;
                debug(L"PreferredRefreshRate: Default");
            }
        }

        if (lstrcmpi(sSwapChainBufferCount.c_str(), L"Default") == 0)
        {
            g_SetSwapChainBufferCount = false;
            debug(L"SwapChainBufferCount: Default");
        }
        else
        {
            try
            {
                g_SwapChainBufferCount = std::stoi(sSwapChainBufferCount);
                g_SetSwapChainBufferCount = true;
                debug(L"SwapChainBufferCount: %d", g_SwapChainBufferCount);
            }
            catch (std::invalid_argument)
            {
                g_SetSwapChainBufferCount = false;
                debug(L"SwapChainBufferCount: Default");
            }
        }

        if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_DISCARD") == 0)
        {
            g_SetSwapEffect = true;
            g_SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            debug(L"SwapEffect: DXGI_SWAP_EFFECT_DISCARD");
        }
        else if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_SEQUENTIAL") == 0)
        {
            g_SetSwapEffect = true;
            g_SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
            debug(L"SwapEffect: DXGI_SWAP_EFFECT_SEQUENTIAL");
        }
        else if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_FLIP_DISCARD") == 0)
        {
            g_SetSwapEffect = true;
            g_SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            debug(L"SwapEffect: DXGI_SWAP_EFFECT_FLIP_DISCARD");
        }
        else if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL") == 0)
        {
            g_SetSwapEffect = true;
            g_SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
            debug(L"SwapEffect: DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL");
        }
        else
        {
            g_SetSwapEffect = false;
            debug(L"SwapEffect: Default");
        }

        if (lstrcmpi(sMaximumFrameLatency.c_str(), L"Default") == 0)
        {
            g_SetMaximumFrameLatency = false;
            debug(L"MaximumFrameLatency: Default");
        }
        else
        {
            try
            {
                g_MaximumFrameLatency = std::stoi(sMaximumFrameLatency);
                g_SetMaximumFrameLatency = true;
                debug(L"MaximumFrameLatency: %d", g_MaximumFrameLatency);
            }
            catch (std::invalid_argument)
            {
                g_SetMaximumFrameLatency = false;
                debug(L"MaximumFrameLatency: Default");
            }
        }

        if (lstrcmpi(sAllowTearing.c_str(), L"On") == 0)
        {
            g_SetAllowTearing = true;
            g_AllowTearing = true;
            debug(L"AllowTearing: On");
        }
        if (lstrcmpi(sAllowTearing.c_str(), L"Off") == 0)
        {
            g_SetAllowTearing = true;
            g_AllowTearing = false;
            debug(L"AllowTearing: Off");
        }
        else
        {
            g_SetAllowTearing = false;
            debug(L"AllowTearing: Default");
        }

        if (lstrcmpi(sFPSLimit.c_str(), L"Off") == 0)
        {
            g_SetFPSLimit = false;
            debug(L"FPSLimit: Off");
        }
        else
        {
            try
            {
                g_FPSLimit = std::stoi(sFPSLimit);
                g_SetFPSLimit = true;
                debug(L"FPSLimit: %d", g_FPSLimit);
            }
            catch (std::invalid_argument)
            {
                g_SetFPSLimit = false;
                debug(L"FPSLimit: Off");
            }
        }

        if (lstrcmpi(sDXGIHooking.c_str(), L"Off") == 0)
        {
            g_DXGIHooking = false;
            debug(L"DXGIHooking: Off");
        }
        else
        {
            g_DXGIHooking = true;
            debug(L"DXGIHooking: On");
        }

        // this is important as without this, compatibility options are not passed to the app!
        // eg. "Disabled fullscreen optimizations" (and possibly other compatibility options) won't work.
        // SetAppCompatStringPointer is called before the dll is even loaded somehow?!?!? (WTF?)
        // it gets called before DllMain and before anything is loaded really, so the handling for it is a bit special.
        // the hooked function just saves the string passed to it and then it is passed to the real function here.
        if (g_CchAppCompatString)
        {
            SetAppCompatStringPointerProc *RealSetAppCompatStringPointer = (SetAppCompatStringPointerProc *)GetProcAddress2(DXGI_DLL_PATH, "SetAppCompatStringPointer");
            RealSetAppCompatStringPointer(g_CchAppCompatString, g_AppCompatString);
            // {
            //     static char test[] = "ForceWARP=0;DisableMaximizedWindowedFullscreen=1;DisableMaximizedWindowedUpgrades=1;Hybrid=0;LowVidMemCap=0;EnableGraphicsPerfMonitor=0;DisableVrrSyncIntervalOverride=1";
            //     RealSetAppCompatStringPointer(sizeof(test), test);
            // }
        }

        // g_D3D12CreateDevice_UndoPatch = PatchAddress(D3D12CreateDevice, FakeD3D12CreateDevice);
        break;
    }

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE; // Successful DLL_PROCESS_ATTACH.
}

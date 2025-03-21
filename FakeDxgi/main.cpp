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
    // return RealCreateDXGIFactory(riid, ppFactory);
}

typedef HRESULT WINAPI CreateDXGIFactory1Proc(REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory1");

    static CreateDXGIFactory1Proc *RealCreateDXGIFactory1 = (CreateDXGIFactory1Proc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory1");

    HRESULT hr = RealCreateDXGIFactory1(riid, ppFactory);
    if (SUCCEEDED(hr) && g_DXGIHooking)
    {
        // we want to ensure that we have the correct riid because the system can pass in other values
        if (IsEqualIID(riid, __uuidof(IDXGIFactory1)))
        {
            *ppFactory = GetProxyFor<DXGIFactoryProxy>((IDXGIFactory1 *)*ppFactory);
        }
        else
        {
            debug(L"-> Internal system call. Ignoring.");
        }
    }
    return hr;
    // return RealCreateDXGIFactory1(riid, ppFactory);
}

typedef HRESULT WINAPI CreateDXGIFactory2Proc(UINT Flags, REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory2");

    static CreateDXGIFactory2Proc *RealCreateDXGIFactory2 = (CreateDXGIFactory2Proc *)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory2");

    HRESULT hr = RealCreateDXGIFactory2(Flags, riid, ppFactory);

    if (SUCCEEDED(hr) && g_DXGIHooking)
    {
        // we want to ensure that we have the correct riid because the system can pass in other values
        if (IsEqualIID(riid, __uuidof(IDXGIFactory2)))
        {
            *ppFactory = GetProxyFor<DXGIFactoryProxy>((IDXGIFactory2 *)*ppFactory);
        }
        else
        {
            debug(L"-> Internal system call. Ignoring.");
        }
    }
    return hr;
    // return RealCreateDXGIFactory2(Flags, riid, ppFactory);
}

typedef HRESULT WINAPI DXGIGetDebugInterface1Proc(UINT Flags, REFIID riid, _Out_ void **ppFactory);

HRESULT WINAPI DXGIGetDebugInterface1(UINT Flags, REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"DXGIGetDebugInterface1");

    static DXGIGetDebugInterface1Proc *RealDXGIGetDebugInterface1 = (DXGIGetDebugInterface1Proc *)GetProcAddress2(DXGI_DLL_PATH, "DXGIGetDebugInterface1");

    return RealDXGIGetDebugInterface1(Flags, riid, ppFactory);
}

// d3d11 patching

undo_patch *g_D3D11CreateDevice_UndoPatch;

HRESULT WINAPI FakeD3D11CreateDevice(
    _In_opt_ IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _Out_opt_ ID3D11Device **ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL *pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext **ppImmediateContext)
{
    inc_dbg_level(L"D3D11CreateDevice");

    UndoPatch(g_D3D11CreateDevice_UndoPatch);

    g_StahpBruh++;
    HRESULT hr = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
    g_StahpBruh--;
    if (SUCCEEDED(hr) && g_D3D11Hooking)
    {
        if (ppDevice && *ppDevice)
            *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
    }

    g_D3D11CreateDevice_UndoPatch = PatchAddress((LPVOID)D3D11CreateDevice, (LPVOID)FakeD3D11CreateDevice);
    return hr;
}

undo_patch *g_D3D11CreateDeviceAndSwapChain_UndoPatch;

HRESULT WINAPI FakeD3D11CreateDeviceAndSwapChain(
    _In_opt_ IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _In_opt_ CONST DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    _Out_opt_ IDXGISwapChain **ppSwapChain,
    _Out_opt_ ID3D11Device **ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL *pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext **ppImmediateContext)
{
    inc_dbg_level(L"D3D11CreateDeviceAndSwapChain");

    UndoPatch(g_D3D11CreateDeviceAndSwapChain_UndoPatch);

    g_StahpBruh++;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
    g_StahpBruh--;
    if (SUCCEEDED(hr) && g_D3D11Hooking)
    {
        if (ppDevice && *ppDevice)
            *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
        if (ppSwapChain && *ppSwapChain)
            *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
    }

    g_D3D11CreateDeviceAndSwapChain_UndoPatch = PatchAddress((LPVOID)D3D11CreateDeviceAndSwapChain, (LPVOID)FakeD3D11CreateDeviceAndSwapChain);
    return hr;
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
            debug(L"DXGIHoohking: Off");
        }
        else
        {
            g_DXGIHooking = true;
            debug(L"DXGIHoohking: On");
        }

        if (lstrcmpi(sD3D11Hooking.c_str(), L"On") == 0)
        {
            g_D3D11Hooking = true;
            debug(L"D3D11Hoohking: On");
        }
        else
        {
            g_D3D11Hooking = false;
            debug(L"D3D11Hoohking: Off");
        }

        // this is important as without this, compatibility options are not passed to the app!
        // eg. "Disabled fullscreen optimizations" (and possibly other compatibility options) won't work.
        // SetAppCompatStringPointer is called before the dll is even loaded somehow?!?!? (WTF?)
        // it gets called before DllMain and before anything is loaded really, so the handling for it is a bit special.
        // the hooked function just saves the string passed to it and then it is passed to the real function here.
        {
            // SetAppCompatStringPointerProc *RealSetAppCompatStringPointer = (SetAppCompatStringPointerProc *)GetProcAddress2(DXGI_DLL_PATH, "SetAppCompatStringPointer");
            // static char test[] = "ForceWARP=1;DisableMaximizedWindowedFullscreen=1;DisableMaximizedWindowedUpgrades=1;Hybrid=0;LowVidMemCap=1;EnableGraphicsPerfMonitor=0;DisableVrrSyncIntervalOverride=1";
            // RealSetAppCompatStringPointer(sizeof(test), test);
        }
        if (g_CchAppCompatString)
        {
            SetAppCompatStringPointerProc *RealSetAppCompatStringPointer = (SetAppCompatStringPointerProc *)GetProcAddress2(DXGI_DLL_PATH, "SetAppCompatStringPointer");
            RealSetAppCompatStringPointer(g_CchAppCompatString, g_AppCompatString);
        }

        g_D3D11CreateDevice_UndoPatch = PatchAddress((LPVOID)D3D11CreateDevice, (LPVOID)FakeD3D11CreateDevice);
        g_D3D11CreateDeviceAndSwapChain_UndoPatch = PatchAddress((LPVOID)D3D11CreateDeviceAndSwapChain, (LPVOID)FakeD3D11CreateDeviceAndSwapChain);

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

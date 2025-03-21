#include "FPSSmoother/D3D11DeviceProxy.h"
#include "FPSSmoother/DXGISwapChainProxy.h"
#include "FPSSmoother/DXGIFactoryProxy.h"
#include "FPSSmoother/Util.h"
#include "main.h"
#include "PatchJmp/PatchJmp.h"

#include <stdio.h>
#include <Shlwapi.h>
#include <string>
#include <d3d11_2.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Shlwapi.lib")


#define D3D11_DLL_PATH "C:\\Windows\\System32\\d3d11.dll"
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


typedef HRESULT WINAPI D3D11CreateDeviceProc(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _Out_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext** ppImmediateContext);

HRESULT WINAPI D3D11CreateDevice(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _Out_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    inc_dbg_level(L"D3D11CreateDevicea");

    static D3D11CreateDeviceProc* RealD3D11CreateDevice = (D3D11CreateDeviceProc*)GetProcAddress2(D3D11_DLL_PATH, "D3D11CreateDevice");

    HRESULT hr = RealD3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
    if (SUCCEEDED(hr))
    {
        *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
    }
    return hr;
}


typedef HRESULT WINAPI D3D11CreateDeviceAndSwapChainProc(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    _Out_opt_ IDXGISwapChain** ppSwapChain,
    _Out_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext** ppImmediateContext);

HRESULT WINAPI D3D11CreateDeviceAndSwapChain(
    _In_opt_ IDXGIAdapter* pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    _In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    _In_opt_ CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
    _Out_opt_ IDXGISwapChain** ppSwapChain,
    _Out_opt_ ID3D11Device** ppDevice,
    _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
    _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
{
    inc_dbg_level(L"D3D11CreateDeviceAndSwapChaina");

    static D3D11CreateDeviceAndSwapChainProc* RealD3D11CreateDeviceAndSwapChain = (D3D11CreateDeviceAndSwapChainProc*)GetProcAddress2(D3D11_DLL_PATH, "D3D11CreateDeviceAndSwapChain");

    HRESULT hr = RealD3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
    if (SUCCEEDED(hr))
    {
        *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
        if (ppSwapChain)
            *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
    }

    return hr;
}





typedef HRESULT WINAPI CreateDXGIFactoryProc(REFIID riid, _Out_ void **ppFactory);
typedef HRESULT WINAPI CreateDXGIFactory1Proc(REFIID riid, _Out_ void **ppFactory);
typedef HRESULT WINAPI CreateDXGIFactory2Proc(UINT Flags, REFIID riid, _Out_ void **ppFactory);

CreateDXGIFactoryProc* g_RealCreateDXGIFactory;
CreateDXGIFactory1Proc* g_RealCreateDXGIFactory1;
CreateDXGIFactory2Proc* g_RealCreateDXGIFactory2;

undo_patch* g_CreateDXGIFactory_UndoPatch;

HRESULT WINAPI FakeCreateDXGIFactory(REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory");

    UndoPatch(g_CreateDXGIFactory_UndoPatch);

    HRESULT hr = g_RealCreateDXGIFactory(riid, ppFactory);
    if (SUCCEEDED(hr))
    {
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory1>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory2>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory3>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory4>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory5>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory6>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory7>(riid, ppFactory);
        proxyHelper.AndThankYou(riid, ppFactory);
    }

    g_CreateDXGIFactory_UndoPatch = PatchAddress((LPVOID)g_RealCreateDXGIFactory, (LPVOID)FakeCreateDXGIFactory);
    return hr;
}


undo_patch* g_CreateDXGIFactory1_UndoPatch;

HRESULT WINAPI FakeCreateDXGIFactory1(REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory1");

    UndoPatch(g_CreateDXGIFactory1_UndoPatch);

    HRESULT hr = g_RealCreateDXGIFactory1(riid, ppFactory);
    if (SUCCEEDED(hr))
    {
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory1>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory2>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory3>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory4>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory5>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory6>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory7>(riid, ppFactory);
        proxyHelper.AndThankYou(riid, ppFactory);
    }

    g_CreateDXGIFactory1_UndoPatch = PatchAddress((LPVOID)g_RealCreateDXGIFactory1, (LPVOID)FakeCreateDXGIFactory1);
    return hr;
}



undo_patch* g_CreateDXGIFactory2_UndoPatch;

HRESULT WINAPI FakeCreateDXGIFactory2(UINT Flags, REFIID riid, _Out_ void **ppFactory)
{
    inc_dbg_level(L"CreateDXGIFactory2");

    UndoPatch(g_CreateDXGIFactory2_UndoPatch);

    HRESULT hr = g_RealCreateDXGIFactory2(Flags, riid, ppFactory);
    if (SUCCEEDED(hr))
    {
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory1>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory2>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory3>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory4>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory5>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory6>(riid, ppFactory);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory7>(riid, ppFactory);
        proxyHelper.AndThankYou(riid, ppFactory);
    }

    g_CreateDXGIFactory2_UndoPatch = PatchAddress((LPVOID)g_RealCreateDXGIFactory2, (LPVOID)FakeCreateDXGIFactory2);
    return hr;
}






BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
#ifdef DEBUG_BUILD
        AllocConsole();
        FILE* oldStream = NULL;
        freopen_s(&oldStream, "CONOUT$", "w", stdout);
#endif

        g_RealCreateDXGIFactory = (CreateDXGIFactoryProc*)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory");
        g_RealCreateDXGIFactory1 = (CreateDXGIFactory1Proc*)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory1");
        g_RealCreateDXGIFactory2 = (CreateDXGIFactory2Proc*)GetProcAddress2(DXGI_DLL_PATH, "CreateDXGIFactory2");


        g_CreateDXGIFactory_UndoPatch = PatchAddress((LPVOID)g_RealCreateDXGIFactory, (LPVOID)FakeCreateDXGIFactory);
        g_CreateDXGIFactory1_UndoPatch = PatchAddress((LPVOID)g_RealCreateDXGIFactory1, (LPVOID)FakeCreateDXGIFactory1);
        g_CreateDXGIFactory2_UndoPatch = PatchAddress((LPVOID)g_RealCreateDXGIFactory2, (LPVOID)FakeCreateDXGIFactory2);

        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
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
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}


#include "FPSSmoother/Proxies/DXGISwapChainProxy.h"
#include "FPSSmoother/Proxies/D3D11DeviceProxy.h"
#include "FPSSmoother/utils.h"
#include "PatchJmp/PatchJmp.h"

#include <Windows.h>
#include <d3d11.h>
#include <d3d11on12.h>

#define D3D11_DLL_PATH "C:\\Windows\\System32\\d3d11.dll"

// d3d11 patching
using D3D11CreateDeviceProc = decltype(&D3D11CreateDevice);
D3D11CreateDeviceProc D3D11CreateDeviceReal = nullptr;
undo_patch *g_D3D11CreateDevice_UndoPatch;

HRESULT WINAPI FakeD3D11CreateDevice(
    IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    ID3D11Device **ppDevice,
    D3D_FEATURE_LEVEL *pFeatureLevel,
    ID3D11DeviceContext **ppImmediateContext)
{
    inc_dbg_level(L"FakeD3D11CreateDevice");

    UndoPatch(g_D3D11CreateDevice_UndoPatch);

    HRESULT hr = D3D11CreateDeviceReal(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
    if (SUCCEEDED(hr))
    {
        *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
    }

    g_D3D11CreateDevice_UndoPatch = PatchAddress((LPVOID)D3D11CreateDeviceReal, (LPVOID)FakeD3D11CreateDevice);
    return hr;
}

using D3D11CreateDeviceAndSwapChainProc = decltype(&D3D11CreateDeviceAndSwapChain);
D3D11CreateDeviceAndSwapChainProc D3D11CreateDeviceAndSwapChainReal = nullptr;
undo_patch *g_D3D11CreateDeviceAndSwapChain_UndoPatch;

HRESULT FakeD3D11CreateDeviceAndSwapChain(
    IDXGIAdapter *pAdapter,
    D3D_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    const D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    UINT SDKVersion,
    const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    IDXGISwapChain **ppSwapChain,
    ID3D11Device **ppDevice,
    D3D_FEATURE_LEVEL *pFeatureLevel,
    ID3D11DeviceContext **ppImmediateContext)
{
    inc_dbg_level(L"FakeD3D11CreateDeviceAndSwapChain");

    UndoPatch(g_D3D11CreateDeviceAndSwapChain_UndoPatch);

    HRESULT hr = D3D11CreateDeviceAndSwapChainReal(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
    if (SUCCEEDED(hr))
    {
        // *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
        // *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
    }

    g_D3D11CreateDeviceAndSwapChain_UndoPatch = PatchAddress((LPVOID)D3D11CreateDeviceAndSwapChainReal, (LPVOID)FakeD3D11CreateDeviceAndSwapChain);
    return hr;
}

using D3D11On12CreateDeviceProc = decltype(&D3D11On12CreateDevice);
D3D11On12CreateDeviceProc D3D11On12CreateDeviceReal = nullptr;
undo_patch *g_D3D11On12CreateDevice_UndoPatch;

HRESULT FakeD3D11On12CreateDevice(
    IUnknown *pDevice,
    UINT Flags,
    const D3D_FEATURE_LEVEL *pFeatureLevels,
    UINT FeatureLevels,
    IUnknown *const *ppCommandQueues,
    UINT NumQueues,
    UINT NodeMask,
    ID3D11Device **ppDevice,
    ID3D11DeviceContext **ppImmediateContext,
    D3D_FEATURE_LEVEL *pChosenFeatureLevel)
{
    inc_dbg_level(L"FakeD3D11On12CreateDevice");

    UndoPatch(g_D3D11On12CreateDevice_UndoPatch);

    HRESULT hr = D3D11On12CreateDeviceReal(pDevice, Flags, pFeatureLevels, FeatureLevels, ppCommandQueues, NumQueues, NodeMask, ppDevice, ppImmediateContext, pChosenFeatureLevel);
    if (SUCCEEDED(hr))
    {
        *ppDevice = GetProxyFor<D3D11DeviceProxy>(*ppDevice);
    }

    g_D3D11On12CreateDevice_UndoPatch = PatchAddress((LPVOID)D3D11On12CreateDeviceReal, (LPVOID)FakeD3D11On12CreateDevice);
    return hr;
}

void PatchD3D11()
{
    D3D11CreateDeviceReal = (D3D11CreateDeviceProc)GetProcAddress2(D3D11_DLL_PATH, "D3D11CreateDevice");
    D3D11CreateDeviceAndSwapChainReal = (D3D11CreateDeviceAndSwapChainProc)GetProcAddress2(D3D11_DLL_PATH, "D3D11CreateDeviceAndSwapChain");
    D3D11On12CreateDeviceReal = (D3D11On12CreateDeviceProc)GetProcAddress2(D3D11_DLL_PATH, "D3D11On12CreateDevice");

    g_D3D11CreateDevice_UndoPatch = PatchAddress((LPVOID)D3D11CreateDeviceReal, (LPVOID)FakeD3D11CreateDevice);
    g_D3D11CreateDeviceAndSwapChain_UndoPatch = PatchAddress((LPVOID)D3D11CreateDeviceAndSwapChainReal, (LPVOID)FakeD3D11CreateDeviceAndSwapChain);
    g_D3D11On12CreateDevice_UndoPatch = PatchAddress((LPVOID)D3D11On12CreateDeviceReal, (LPVOID)FakeD3D11On12CreateDevice);
}

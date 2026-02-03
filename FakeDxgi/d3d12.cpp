#include <Windows.h>
#include <pathcch.h>
#include <d3d12.h>

#include "FPSSmoother/utils.h"
#include "FPSSmoother/proxy_utils.h"
#include "PatchJmp/PatchJmp.h"

#define D3D12_DLL_PATH "C:\\Windows\\System32\\d3d12.dll"

// d3d12 patching
using D3D12CreateDeviceProc = decltype(&D3D12CreateDevice);
D3D12CreateDeviceProc RealD3D12CreateDevice = nullptr;
undo_patch *g_D3D12CreateDevice_UndoPatch;

HRESULT WINAPI FakeD3D12CreateDevice(
    IUnknown *pAdapter,
    D3D_FEATURE_LEVEL MinimumFeatureLevel,
    REFIID riid,
    void **ppDevice)
{
    inc_dbg_level(L"FakeD3D12CreateDevice");

    UndoPatch(g_D3D12CreateDevice_UndoPatch);

    HRESULT hr = RealD3D12CreateDevice(pAdapter, MinimumFeatureLevel, riid, ppDevice);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppDevice);
    }

    g_D3D12CreateDevice_UndoPatch = PatchAddress((LPVOID)RealD3D12CreateDevice, (LPVOID)FakeD3D12CreateDevice);
    return hr;
}

void PatchD3D12()
{
    RealD3D12CreateDevice = (D3D12CreateDeviceProc)GetProcAddress2(D3D12_DLL_PATH, "D3D12CreateDevice");

    g_D3D12CreateDevice_UndoPatch = PatchAddress((LPVOID)RealD3D12CreateDevice, (LPVOID)FakeD3D12CreateDevice);
}

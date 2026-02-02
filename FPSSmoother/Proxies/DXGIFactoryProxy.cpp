#include <d3d12.h>

#include "DXGIFactoryProxy.h"
#include "DXGISwapChainProxy.h"
#include "DXGIAdapterProxy.h"
#include "DXGIObjectProxy.h"
#include "../globals.h"
#include "../utils.h"

HRESULT DXGIFactoryProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"DXGIFactoryProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _factory->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        DXGIFactoryProxy::QueryProxy(riid, ppvObject);
    }

    return hr;
}

ULONG DXGIFactoryProxy::AddRef(void)
{
    inc_dbg_level(L"DXGIFactoryProxy::AddRef");

    return _factory->AddRef();
}

ULONG DXGIFactoryProxy::Release(void)
{
    inc_dbg_level(L"DXGIFactoryProxy::Release");

    return _factory->Release();
}

HRESULT DXGIFactoryProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
    return _factory->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIFactoryProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
    return _factory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIFactoryProxy::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
    return _factory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIFactoryProxy::GetParent(REFIID riid, void **ppParent)
{
    inc_dbg_level(L"DXGIFactoryProxy::GetParent");

    HRESULT hr = _factory->GetParent(riid, ppParent);
    if (SUCCEEDED(hr))
    {
        DXGIObjectProxy::QueryProxy(riid, ppParent);
    }

    return hr;
}

HRESULT DXGIFactoryProxy::EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumAdapters");

    HRESULT hr = _factory->EnumAdapters(Adapter, ppAdapter);
    if (SUCCEEDED(hr))
    {
        *ppAdapter = static_cast<IDXGIAdapter *>(GetProxyFor<DXGIAdapterProxy>(*ppAdapter));
    }
    return hr;
}

HRESULT DXGIFactoryProxy::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
    return _factory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT DXGIFactoryProxy::GetWindowAssociation(HWND *pWindowHandle)
{
    return _factory->GetWindowAssociation(pWindowHandle);
}

HRESULT DXGIFactoryProxy::CreateSwapChain(IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain)
{
    inc_dbg_level(L"DXGIFactoryProxy::CreateSwapChain");

    bool isD3D12 = false;
    bool handleD3D12MaximumFrameLatency = false;

    ID3D12CommandQueue *d3d12CommandQueue = nullptr;
    pDevice->QueryInterface(&d3d12CommandQueue);
    if (d3d12CommandQueue)
    {
        isD3D12 = true;
        d3d12CommandQueue->Release();
    }

    if (g_SetSwapChainBufferCount)
        pDesc->BufferCount = g_SwapChainBufferCount;
    if (g_SetPreferredRefreshRate)
        pDesc->BufferDesc.RefreshRate.Numerator = g_PreferredRefreshRate;
    if (g_SetSwapEffect)
        pDesc->SwapEffect = g_SwapEffect;
    if (g_SetMaximumFrameLatency)
    {
        if (isD3D12 && (pDesc->Flags & DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT) == 0)
        {
            handleD3D12MaximumFrameLatency = true;
            pDesc->Flags |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        }
        else
        {
            IDXGIDevice1 *pDXGIDevice;
            HRESULT hr = pDevice->QueryInterface(&pDXGIDevice);
            if (SUCCEEDED(hr))
            {
                pDXGIDevice->SetMaximumFrameLatency(g_MaximumFrameLatency);
                pDXGIDevice->Release();
            }
        }
    }
    if (g_SetAllowTearing)
    {
        if (g_AllowTearing)
            pDesc->Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        else
            pDesc->Flags &= ~DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    }
    if (g_SetFullscreenMode)
        pDesc->Windowed = g_FullscreenMode ? FALSE : TRUE;

    g_StahpBruh++;
    HRESULT hr = _factory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
    g_StahpBruh--;
    if (SUCCEEDED(hr))
    {
        debug(L"-> Is D3D12: %d", isD3D12);
        debug(
            L"-> Mode: %dx%d RefreshRate: %d Windowed: %d",
            pDesc->BufferDesc.Width,
            pDesc->BufferDesc.Height,
            pDesc->BufferDesc.RefreshRate.Numerator,
            pDesc->Windowed);
        debug(L"-> BufferCount: %d SwapEffect: %s", pDesc->BufferCount, SwapChainSwapEffectToStr(pDesc->SwapEffect));
        debug(L"-> Flags: %s", SwapChainFlagsToStr(pDesc->Flags));

        *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
        if (g_SetMaximumFrameLatency && isD3D12)
        {
            if (handleD3D12MaximumFrameLatency)
                ((DXGISwapChainProxy *)*ppSwapChain)->EnableD3D12MaximumFrameLatencyHandling();
            else
                ((DXGISwapChainProxy *)*ppSwapChain)->ApplyMaximumFrameLatency();
        }
    }
    return hr;
}

HRESULT DXGIFactoryProxy::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::CreateSoftwareAdapter");

    return _factory->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT DXGIFactoryProxy::EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumAdapters1");

    if (_factory1)
    {
        HRESULT hr = _factory1->EnumAdapters1(Adapter, ppAdapter);
        if (SUCCEEDED(hr))
        {
            *ppAdapter = GetProxyFor<DXGIAdapterProxy>(*ppAdapter);
        }
        return hr;
    }

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

BOOL DXGIFactoryProxy::IsCurrent(void)
{
    inc_dbg_level(L"DXGIFactoryProxy::IsCurrent");

    if (_factory1)
        return _factory1->IsCurrent();

    debug(L"Warning: Not implemented code path reached.");
    return FALSE;
}

BOOL DXGIFactoryProxy::IsWindowedStereoEnabled(void)
{
    inc_dbg_level(L"IsWindowedStereoEnabled::IsCurrent");

    if (_factory2)
        return _factory2->IsWindowedStereoEnabled();

    debug(L"Warning: Not implemented code path reached.");
    return FALSE;
}

HRESULT DXGIFactoryProxy::CreateSwapChainForHwnd(IUnknown *pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 *pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
{
    inc_dbg_level(L"DXGIFactoryProxy::CreateSwapChainForHwnd");

    if (_factory2)
    {
        bool isD3D12 = false;
        bool handleD3D12MaximumFrameLatency = false;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc{};
        if (pFullscreenDesc)
            fullscreenDesc = *pFullscreenDesc;
        else
        {
            fullscreenDesc.RefreshRate.Numerator = 0;
            fullscreenDesc.RefreshRate.Denominator = 0;
            fullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            fullscreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            fullscreenDesc.Windowed = TRUE;
        }

        ID3D12CommandQueue *d3d12CommandQueue = nullptr;
        pDevice->QueryInterface(&d3d12CommandQueue);
        if (d3d12CommandQueue)
        {
            isD3D12 = true;
            d3d12CommandQueue->Release();
        }

        if (g_SetSwapChainBufferCount)
            ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->BufferCount = g_SwapChainBufferCount;
        if (g_SetPreferredRefreshRate)
            fullscreenDesc.RefreshRate.Numerator = g_PreferredRefreshRate;
        if (g_SetSwapEffect)
            ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->SwapEffect = g_SwapEffect;
        if (g_SetMaximumFrameLatency)
        {
            if (isD3D12 && (pDesc->Flags & DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT) == 0)
            {
                handleD3D12MaximumFrameLatency = true;
                ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->Flags |= DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
            }
            else
            {
                IDXGIDevice1 *pDXGIDevice;
                HRESULT hr = pDevice->QueryInterface(&pDXGIDevice);
                if (SUCCEEDED(hr))
                {
                    pDXGIDevice->SetMaximumFrameLatency(g_MaximumFrameLatency);
                    pDXGIDevice->Release();
                }
            }
        }
        if (g_SetAllowTearing)
        {
            if (g_AllowTearing)
                ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
            else
                ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->Flags &= ~DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        }
        if (g_SetFullscreenMode)
            fullscreenDesc.Windowed = g_FullscreenMode ? FALSE : TRUE;

        g_StahpBruh++;
        HRESULT hr = _factory2->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, &fullscreenDesc, pRestrictToOutput, ppSwapChain);
        g_StahpBruh--;
        if (SUCCEEDED(hr))
        {
            debug(L"-> Is D3D12: %d", isD3D12);
            debug(L"-> Resolution: %dx%d ", pDesc->Width, pDesc->Height);
            debug(L"-> RefreshRate: %d Windowed: %d", fullscreenDesc.RefreshRate.Numerator, fullscreenDesc.Windowed);
            debug(L"-> BufferCount: %d SwapEffect: %s", pDesc->BufferCount, SwapChainSwapEffectToStr(pDesc->SwapEffect));
            debug(L"-> Flags: %s", SwapChainFlagsToStr(pDesc->Flags));

            *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
            if (g_SetMaximumFrameLatency && isD3D12)
            {
                if (handleD3D12MaximumFrameLatency)
                    ((DXGISwapChainProxy *)*ppSwapChain)->EnableD3D12MaximumFrameLatencyHandling();
                else
                    ((DXGISwapChainProxy *)*ppSwapChain)->ApplyMaximumFrameLatency();
            }
        }
        return hr;
    }
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::CreateSwapChainForCoreWindow(IUnknown *pDevice, IUnknown *pWindow, const DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
{
    inc_dbg_level(L"DXGIFactoryProxy::CreateSwapChainForCoreWindow");

    if (_factory2)
        return _factory2->CreateSwapChainForCoreWindow(pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::GetSharedResourceAdapterLuid(HANDLE hResource, LUID *pLuid)
{
    inc_dbg_level(L"DXGIFactoryProxy::GetSharedResourceAdapterLuid");

    if (_factory2)
        return _factory2->GetSharedResourceAdapterLuid(hResource, pLuid);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::RegisterStereoStatusWindow");

    if (_factory2)
        return _factory2->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::RegisterStereoStatusEvent(HANDLE hEvent, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::RegisterStereoStatusEvent");

    if (_factory2)
        return _factory2->RegisterStereoStatusEvent(hEvent, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void DXGIFactoryProxy::UnregisterStereoStatus(DWORD dwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::UnregisterStereoStatus");

    if (_factory2)
        _factory2->UnregisterStereoStatus(dwCookie);

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT DXGIFactoryProxy::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::RegisterOcclusionStatusWindow");

    if (_factory2)
        return _factory2->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::RegisterOcclusionStatusEvent");

    if (_factory2)
        return _factory2->RegisterOcclusionStatusEvent(hEvent, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void DXGIFactoryProxy::UnregisterOcclusionStatus(DWORD dwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::UnregisterOcclusionStatus");

    if (_factory2)
        _factory2->UnregisterOcclusionStatus(dwCookie);

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT DXGIFactoryProxy::CreateSwapChainForComposition(IUnknown *pDevice, const DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain)
{
    inc_dbg_level(L"DXGIFactoryProxy::CreateSwapChainForComposition");

    if (_factory2)
        return _factory2->CreateSwapChainForComposition(pDevice, pDesc, pRestrictToOutput, ppSwapChain);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

UINT DXGIFactoryProxy::GetCreationFlags(void)
{
    inc_dbg_level(L"DXGIFactoryProxy::GetCreationFlags");

    if (_factory3)
        return _factory3->GetCreationFlags();

    debug(L"Warning: Not implemented code path reached.");
    return 0;
}

HRESULT DXGIFactoryProxy::EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void **ppvAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumAdapterByLuid");

    if (_factory4)
    {
        HRESULT hr = _factory4->EnumAdapterByLuid(AdapterLuid, riid, ppvAdapter);
        if (SUCCEEDED(hr))
        {
            DXGIAdapterProxy::QueryProxy(riid, ppvAdapter);
        }
        return hr;
    }

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::EnumWarpAdapter(REFIID riid, void **ppvAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumWarpAdapter");

    if (_factory4)
        return _factory4->EnumWarpAdapter(riid, ppvAdapter);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::CheckFeatureSupport(DXGI_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize)
{
    inc_dbg_level(L"DXGIFactoryProxy::CheckFeatureSupport");

    if (_factory5)
        return _factory5->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void **ppvAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumAdapterByGpuPreference");

    if (_factory6)
        return _factory6->EnumAdapterByGpuPreference(Adapter, GpuPreference, riid, ppvAdapter);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::RegisterAdaptersChangedEvent(HANDLE hEvent, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::RegisterAdaptersChangedEvent");

    if (_factory7)
        _factory7->RegisterAdaptersChangedEvent(hEvent, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIFactoryProxy::UnregisterAdaptersChangedEvent(DWORD dwCookie)
{
    inc_dbg_level(L"DXGIFactoryProxy::UnregisterAdaptersChangedEvent");

    if (_factory7)
        _factory7->UnregisterAdaptersChangedEvent(dwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

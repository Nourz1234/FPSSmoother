#include <d3d12.h>

#include "DXGIFactoryProxy.h"
#include "DXGISwapChainProxy.h"
#include "DXGIAdapterProxy.h"
#include "Util.h"
#include "globals.h"

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
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory1>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory2>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory3>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory4>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory5>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory6>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory7>(riid, ppvObject);
        proxyHelper.AndThankYou(riid, ppvObject);
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
        ProxyHelper proxyHelper;
        proxyHelper.AndThankYou(riid, ppParent);
    }

    return hr;
}

HRESULT DXGIFactoryProxy::EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumAdapters");

    // HRESULT hr = _factory->EnumAdapters(Adapter, ppAdapter);
    // if (SUCCEEDED(hr))
    //{
    //	*ppAdapter = static_cast<IDXGIAdapter*>(DXGIAdapterProxy::GetProxyFor(*ppAdapter));
    // }
    // return hr;
    return _factory->EnumAdapters(Adapter, ppAdapter);
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

    // if (g_StahpBruh)
    // {
    //     debug(L"-> Stahp!");
    //     return _factory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
    // }

    ID3D12CommandQueue *d3d12CommandQueue;
    pDevice->QueryInterface(&d3d12CommandQueue);
    if (d3d12CommandQueue)
    {
        debug(L"-> D3D12 detected!");
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
        IDXGIDevice1 *pDXGIDevice;
        HRESULT hr = pDevice->QueryInterface(&pDXGIDevice);
        if (SUCCEEDED(hr))
        {
            pDXGIDevice->SetMaximumFrameLatency(g_MaximumFrameLatency);

            pDXGIDevice->Release();
        }
    }
    if (g_SetAllowTearing)
    {
        if (g_AllowTearing)
            pDesc->Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        else
            pDesc->Flags &= ~DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    }

    g_StahpBruh++;
    HRESULT hr = _factory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
    g_StahpBruh--;
    if (SUCCEEDED(hr))
    {
        debug(
            L"-> Mode: %dx%d RefreshRate: %d Windowed: %d",
            pDesc->BufferDesc.Width,
            pDesc->BufferDesc.Height,
            pDesc->BufferDesc.RefreshRate.Numerator,
            pDesc->Windowed);
        debug(L"-> BufferCount: %d SwapEffect: %s", pDesc->BufferCount, SwapChainSwapEffectToStr(pDesc->SwapEffect));
        debug(L"-> Flags: %s", SwapChainFlagsToStr(pDesc->Flags));

        IDXGISwapChain2 *swapChain1;
        hr = (*ppSwapChain)->QueryInterface(&swapChain1);
        if (SUCCEEDED(hr))
        {
            swapChain1->SetMaximumFrameLatency(g_MaximumFrameLatency);
            swapChain1->Release();
        }

        *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
    }
    return hr;
    // return _factory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
}

HRESULT DXGIFactoryProxy::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::CreateSoftwareAdapter");

    // HRESULT hr = _factory->CreateSoftwareAdapter(Module, ppAdapter);
    // if (SUCCEEDED(hr))
    // {
    //     *ppAdapter = GetProxyFor<DXGIAdapterProxy>(*ppAdapter);
    // }
    // return hr;
    return _factory->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT DXGIFactoryProxy::EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter)
{
    inc_dbg_level(L"DXGIFactoryProxy::EnumAdapters1");

    if (_factory1)
    {
        // HRESULT hr = _factory1->EnumAdapters1(Adapter, ppAdapter);
        // if (SUCCEEDED(hr))
        // {
        //     *ppAdapter = GetProxyFor<DXGIAdapterProxy>(*ppAdapter);
        // }
        // return hr;
        return _factory1->EnumAdapters1(Adapter, ppAdapter);
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
        ID3D12CommandQueue *d3d12CommandQueue;
        pDevice->QueryInterface(&d3d12CommandQueue);
        if (d3d12CommandQueue)
        {
            debug(L"-> D3D12 detected!");
            d3d12CommandQueue->Release();
        }

        if (g_SetSwapChainBufferCount)
            ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->BufferCount = g_SwapChainBufferCount;
        if (g_SetPreferredRefreshRate)
            ((DXGI_SWAP_CHAIN_FULLSCREEN_DESC *)pFullscreenDesc)->RefreshRate.Numerator = g_PreferredRefreshRate;
        if (g_SetSwapEffect)
            ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->SwapEffect = g_SwapEffect;
        if (g_SetMaximumFrameLatency)
        {
            IDXGIDevice1 *pDXGIDevice;
            HRESULT hr = pDevice->QueryInterface(&pDXGIDevice);
            if (SUCCEEDED(hr))
            {
                pDXGIDevice->SetMaximumFrameLatency(g_MaximumFrameLatency);

                pDXGIDevice->Release();
            }
        }
        if (g_SetAllowTearing)
        {
            if (g_AllowTearing)
                ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->Flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
            else
                ((DXGI_SWAP_CHAIN_DESC1 *)pDesc)->Flags &= ~DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        }

        g_StahpBruh++;
        HRESULT hr = _factory2->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
        g_StahpBruh--;
        if (SUCCEEDED(hr))
        {
            debug(
                L"-> Mode: %dx%d RefreshRate: %d Windowed: %d",
                pDesc->Width,
                pDesc->Height,
                pFullscreenDesc->RefreshRate.Numerator,
                pFullscreenDesc->Windowed);
            debug(L"-> BufferCount: %d SwapEffect: %s", pDesc->BufferCount, SwapChainSwapEffectToStr(pDesc->SwapEffect));
            debug(L"-> Flags: %s", SwapChainFlagsToStr(pDesc->Flags));

            IDXGISwapChain2 *swapChain1;
            hr = (*ppSwapChain)->QueryInterface(&swapChain1);
            if (SUCCEEDED(hr))
            {
                swapChain1->SetMaximumFrameLatency(g_MaximumFrameLatency);
                swapChain1->Release();
            }

            *ppSwapChain = GetProxyFor<DXGISwapChainProxy>(*ppSwapChain);
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
        return _factory4->EnumAdapterByLuid(AdapterLuid, riid, ppvAdapter);

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
    {
        HRESULT hr = _factory6->EnumAdapterByGpuPreference(Adapter, GpuPreference, riid, ppvAdapter);
        if (SUCCEEDED(hr))
        {
            ProxyHelper proxyHelper;
            proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter>(riid, ppvAdapter);
            proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter1>(riid, ppvAdapter);
            proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter2>(riid, ppvAdapter);
            proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter3>(riid, ppvAdapter);
            proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter4>(riid, ppvAdapter);
            proxyHelper.AndThankYou(riid, ppvAdapter);
        }

        return hr;
    }

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

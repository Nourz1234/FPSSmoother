#include "D3D11DeviceProxy.h"
#include "DXGIDeviceProxy.h"
#include "DXGIFactoryProxy.h"
#include "DXGIAdapterProxy.h"
#include "../globals.h"
#include "../utils.h"

inline void DXGIDeviceProxy::QueryProxy(REFIID riid, void **ppvObject)
{
    ProxyHelper proxyHelper;
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice4>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device4>(riid, ppvObject);
    proxyHelper.AndThankYou(riid, ppvObject);
}

HRESULT DXGIDeviceProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"DXGIDeviceProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _device->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        DXGIDeviceProxy::QueryProxy(riid, ppvObject);
    }

    return hr;
}

ULONG DXGIDeviceProxy::AddRef(void)
{
    inc_dbg_level(L"DXGIDeviceProxy::AddRef");

    return _device->AddRef();
}

ULONG DXGIDeviceProxy::Release(void)
{
    inc_dbg_level(L"DXGIDeviceProxy::Release");

    return _device->Release();
}

HRESULT DXGIDeviceProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
    // inc_dbg_level(L"DXGIDeviceProxy::SetPrivateData");

    return _device->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIDeviceProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
    // inc_dbg_level(L"DXGIDeviceProxy::SetPrivateDataInterface");

    return _device->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIDeviceProxy::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
    // inc_dbg_level(L"DXGIDeviceProxy::GetPrivateData");

    return _device->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIDeviceProxy::GetParent(REFIID riid, void **ppParent)
{
    inc_dbg_level(L"DXGIDeviceProxy::GetParent");

    HRESULT hr = _device->GetParent(riid, ppParent);
    if (SUCCEEDED(hr))
    {
        DXGIAdapterProxy::QueryProxy(riid, ppParent);
    }

    return hr;
}

HRESULT DXGIDeviceProxy::GetAdapter(IDXGIAdapter **pAdapter)
{
    inc_dbg_level(L"DXGIDeviceProxy::GetAdapter");

    HRESULT hr = _device->GetAdapter(pAdapter);
    if (SUCCEEDED(hr))
    {
        *pAdapter = GetProxyFor<DXGIAdapterProxy>(*pAdapter);
    }
    return hr;
}

HRESULT DXGIDeviceProxy::CreateSurface(const DXGI_SURFACE_DESC *pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE *pSharedResource, IDXGISurface **ppSurface)
{
    return _device->CreateSurface(pDesc, NumSurfaces, Usage, pSharedResource, ppSurface);
}

HRESULT DXGIDeviceProxy::QueryResourceResidency(IUnknown *const *ppResources, DXGI_RESIDENCY *pResidencyStatus, UINT NumResources)
{
    return _device->QueryResourceResidency(ppResources, pResidencyStatus, NumResources);
}

HRESULT DXGIDeviceProxy::SetGPUThreadPriority(INT Priority)
{
    return _device->SetGPUThreadPriority(Priority);
}

HRESULT DXGIDeviceProxy::GetGPUThreadPriority(INT *pPriority)
{
    return _device->GetGPUThreadPriority(pPriority);
}

HRESULT DXGIDeviceProxy::SetMaximumFrameLatency(UINT MaxLatency)
{
    inc_dbg_level(L"DXGIDeviceProxy::SetMaximumFrameLatency");

    if (_device1)
    {
        if (g_SetMaximumFrameLatency)
            MaxLatency = g_MaximumFrameLatency;

        debug(L"-> MaxLatency: %d", MaxLatency);
        return _device1->SetMaximumFrameLatency(MaxLatency);
    }

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIDeviceProxy::GetMaximumFrameLatency(UINT *pMaxLatency)
{
    inc_dbg_level(L"DXGIDeviceProxy::GetMaximumFrameLatency");

    if (_device1)
        return _device1->GetMaximumFrameLatency(pMaxLatency);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIDeviceProxy::OfferResources(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority)
{
    if (_device2)
        return _device2->OfferResources(NumResources, ppResources, Priority);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIDeviceProxy::ReclaimResources(UINT NumResources, IDXGIResource *const *ppResources, BOOL *pDiscarded)
{
    if (_device2)
        return _device2->ReclaimResources(NumResources, ppResources, pDiscarded);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIDeviceProxy::EnqueueSetEvent(HANDLE hEvent)
{
    if (_device2)
        return _device2->EnqueueSetEvent(hEvent);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void DXGIDeviceProxy::Trim(void)
{
    if (_device3)
        _device3->Trim();

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT DXGIDeviceProxy::OfferResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags)
{
    if (_device4)
        _device4->OfferResources1(NumResources, ppResources, Priority, Flags);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIDeviceProxy::ReclaimResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_RECLAIM_RESOURCE_RESULTS *pResults)
{
    if (_device4)
        _device4->ReclaimResources1(NumResources, ppResources, pResults);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

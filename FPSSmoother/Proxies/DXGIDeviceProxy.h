#pragma once
#include <dxgi1_6.h>
#include "ProxyBase.h"

class DXGIDeviceProxy : public IDXGIDevice4, public ProxyBase
{
    IDXGIDevice *_device = nullptr;
    IDXGIDevice1 *_device1 = nullptr;
    IDXGIDevice2 *_device2 = nullptr;
    IDXGIDevice3 *_device3 = nullptr;
    IDXGIDevice4 *_device4 = nullptr;

public:
    DXGIDeviceProxy(IDXGIDevice *device) : _device(device)
    {
    }
    DXGIDeviceProxy(IDXGIDevice1 *device) : _device(device), _device1(device)
    {
    }
    DXGIDeviceProxy(IDXGIDevice2 *device) : _device(device), _device1(device), _device2(device)
    {
    }
    DXGIDeviceProxy(IDXGIDevice3 *device) : _device(device), _device1(device), _device2(device), _device3(device)
    {
    }
    DXGIDeviceProxy(IDXGIDevice4 *device) : _device(device), _device1(device), _device2(device), _device3(device), _device4(device)
    {
    }

    virtual void CopyTo(ProxyBase *other) override {}

    // Inherited via IDXGIDevice4
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;
    virtual HRESULT STDMETHODCALLTYPE GetAdapter(IDXGIAdapter **pAdapter) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSurface(const DXGI_SURFACE_DESC *pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE *pSharedResource, IDXGISurface **ppSurface) override;
    virtual HRESULT STDMETHODCALLTYPE QueryResourceResidency(IUnknown *const *ppResources, DXGI_RESIDENCY *pResidencyStatus, UINT NumResources) override;
    virtual HRESULT STDMETHODCALLTYPE SetGPUThreadPriority(INT Priority) override;
    virtual HRESULT STDMETHODCALLTYPE GetGPUThreadPriority(INT *pPriority) override;
    virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency) override;
    virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT *pMaxLatency) override;
    virtual HRESULT STDMETHODCALLTYPE OfferResources(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority) override;
    virtual HRESULT STDMETHODCALLTYPE ReclaimResources(UINT NumResources, IDXGIResource *const *ppResources, BOOL *pDiscarded) override;
    virtual HRESULT STDMETHODCALLTYPE EnqueueSetEvent(HANDLE hEvent) override;
    virtual void STDMETHODCALLTYPE Trim(void) override;
    virtual HRESULT STDMETHODCALLTYPE OfferResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags) override;
    virtual HRESULT STDMETHODCALLTYPE ReclaimResources1(UINT NumResources, IDXGIResource *const *ppResources, DXGI_RECLAIM_RESOURCE_RESULTS *pResults) override;
};
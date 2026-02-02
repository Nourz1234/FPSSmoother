#pragma once
#include <dxgi.h>
#include "../utils.h"

class DXGIObjectProxy : public IDXGIObject
{
    IDXGIObject *_object = nullptr;

public:
    DXGIObjectProxy(IDXGIObject *object) : _object(object)
    {
    }

    static inline void QueryProxy(REFIID riid, void **ppvObject)
    {
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIObjectProxy, IDXGIObject>(riid, ppvObject);
        proxyHelper.AndThankYou(riid, ppvObject);
    }

    // Inherited via IDXGIObject
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;
};

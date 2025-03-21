#pragma once
#include <d3d11_2.h>

class DXGIObjectProxy : public IDXGIObject
{
    IDXGIObject* _object = nullptr;
    ULONG m_RefCount = 0;
public:
    DXGIObjectProxy(IDXGIObject* output) : _object(output)
    {
        m_RefCount = 1;
    }
    ~DXGIObjectProxy()
    {
        _object->Release();
    }


    // Inherited via IDXGIObject
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void * pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void ** ppParent) override;
};

#include "DXGIObjectProxy.h"
#include "../globals.h"
#include "../utils.h"
#include "../proxy_utils.h"

HRESULT DXGIObjectProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"DXGIObjectProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _object->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppvObject, this);
    }

    return hr;
}

ULONG DXGIObjectProxy::AddRef(void)
{
    return _object->AddRef();
}

ULONG DXGIObjectProxy::Release(void)
{
    return _object->Release();
}

HRESULT DXGIObjectProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
    return _object->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIObjectProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
    return _object->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIObjectProxy::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
    return _object->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIObjectProxy::GetParent(REFIID riid, void **ppParent)
{
    inc_dbg_level(L"DXGIObjectProxy::GetParent");

    return _object->GetParent(riid, ppParent);
}

#include "DXGIObjectProxy.h"
#include "Util.h"

HRESULT DXGIObjectProxy::QueryInterface(REFIID riid, void ** ppvObject)
{
    HRESULT hr = _object->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        if (IsEqualIID(riid, __uuidof(IDXGIObject)))
        {
            *ppvObject = static_cast<IDXGIObject*>(new DXGIObjectProxy((IDXGIObject*)*ppvObject));
        }
        else
        {
            LPOLESTR pIID = 0;
            StringFromCLSID(riid, &pIID);
            // msgbox(L"DXGIObjectProxy::QueryInterface: %s", pIID);
        }
    }

    return hr;
}

ULONG DXGIObjectProxy::AddRef(void)
{
    return InterlockedIncrement(&m_RefCount);
}

ULONG DXGIObjectProxy::Release(void)
{
    ULONG count = InterlockedDecrement(&m_RefCount);
    if (count == 0) delete this;
    return count;
}

HRESULT DXGIObjectProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void * pData)
{
    return _object->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIObjectProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown)
{
    return _object->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIObjectProxy::GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData)
{
    return _object->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIObjectProxy::GetParent(REFIID riid, void ** ppParent)
{
    LPOLESTR pIID = 0;
    StringFromCLSID(riid, &pIID);
    // msgbox(L"DXGIObjectProxy::GetParent: %s", pIID);

    return _object->GetParent(riid, ppParent);
}

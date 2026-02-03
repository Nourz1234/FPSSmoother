#include "DXGIAdapterProxy.h"
#include "DXGIOutputProxy.h"
#include "../globals.h"
#include "../utils.h"
#include "../proxy_utils.h"

HRESULT DXGIAdapterProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"DXGIAdapterProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _adapter->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppvObject, this);
    }

    return hr;
}

ULONG DXGIAdapterProxy::AddRef(void)
{
    inc_dbg_level(L"DXGIAdapterProxy::AddRef");

    _adapter->AddRef();
    return _adapter->AddRef();
}

ULONG DXGIAdapterProxy::Release(void)
{
    inc_dbg_level(L"DXGIAdapterProxy::Release");

    return _adapter->Release();
}

HRESULT DXGIAdapterProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
    return _adapter->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIAdapterProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
    return _adapter->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIAdapterProxy::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
    return _adapter->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIAdapterProxy::GetParent(REFIID riid, void **ppParent)
{
    inc_dbg_level(L"DXGIAdapterProxy::GetParent");

    HRESULT hr = _adapter->GetParent(riid, ppParent);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppParent);
    }

    return hr;
}

HRESULT DXGIAdapterProxy::EnumOutputs(UINT Output, IDXGIOutput **ppOutput)
{
    inc_dbg_level(L"DXGIAdapterProxy::EnumOutputs");

    HRESULT hr = _adapter->EnumOutputs(Output, ppOutput);
    if (SUCCEEDED(hr))
    {
        *ppOutput = GetProxyFor<DXGIOutputProxy>(*ppOutput);
    }

    return hr;
}

HRESULT DXGIAdapterProxy::GetDesc(DXGI_ADAPTER_DESC *pDesc)
{
    inc_dbg_level(L"DXGIAdapterProxy::GetDesc");

    return _adapter->GetDesc(pDesc);
}

HRESULT DXGIAdapterProxy::CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER *pUMDVersion)
{
    inc_dbg_level(L"DXGIAdapterProxy::CheckInterfaceSupport");

    return _adapter->CheckInterfaceSupport(InterfaceName, pUMDVersion);
}

HRESULT DXGIAdapterProxy::GetDesc1(DXGI_ADAPTER_DESC1 *pDesc)
{
    inc_dbg_level(L"DXGIAdapterProxy::GetDesc1");

    if (_adapter1)
        return _adapter1->GetDesc1(pDesc);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIAdapterProxy::GetDesc2(DXGI_ADAPTER_DESC2 *pDesc)
{
    inc_dbg_level(L"DXGIAdapterProxy::GetDesc2");

    if (_adapter2)
        return _adapter2->GetDesc2(pDesc);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIAdapterProxy::RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIAdapterProxy::RegisterHardwareContentProtectionTeardownStatusEvent");

    if (_adapter3)
        return _adapter3->RegisterHardwareContentProtectionTeardownStatusEvent(hEvent, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void DXGIAdapterProxy::UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie)
{
    inc_dbg_level(L"DXGIAdapterProxy::UnregisterHardwareContentProtectionTeardownStatus");

    if (_adapter3)
        _adapter3->UnregisterHardwareContentProtectionTeardownStatus(dwCookie);

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT DXGIAdapterProxy::QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo)
{
    // inc_dbg_level(L"DXGIAdapterProxy::QueryVideoMemoryInfo");

    if (_adapter3)
        return _adapter3->QueryVideoMemoryInfo(NodeIndex, MemorySegmentGroup, pVideoMemoryInfo);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIAdapterProxy::SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation)
{
    inc_dbg_level(L"DXGIAdapterProxy::SetVideoMemoryReservation");

    if (_adapter3)
        return _adapter3->SetVideoMemoryReservation(NodeIndex, MemorySegmentGroup, Reservation);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIAdapterProxy::RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD *pdwCookie)
{
    inc_dbg_level(L"DXGIAdapterProxy::RegisterVideoMemoryBudgetChangeNotificationEvent");

    if (_adapter3)
        return _adapter3->RegisterVideoMemoryBudgetChangeNotificationEvent(hEvent, pdwCookie);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void DXGIAdapterProxy::UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie)
{
    inc_dbg_level(L"DXGIAdapterProxy::UnregisterVideoMemoryBudgetChangeNotification");

    if (_adapter3)
        return _adapter3->UnregisterVideoMemoryBudgetChangeNotification(dwCookie);

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT DXGIAdapterProxy::GetDesc3(DXGI_ADAPTER_DESC3 *pDesc)
{
    inc_dbg_level(L"DXGIAdapterProxy::GetDesc3");

    if (_adapter4)
        return _adapter4->GetDesc3(pDesc);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

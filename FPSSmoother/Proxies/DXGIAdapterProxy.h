#pragma once
#include <dxgi1_6.h>

class DXGIAdapterProxy : public IDXGIAdapter4
{
    IDXGIAdapter *_adapter = nullptr;
    IDXGIAdapter1 *_adapter1 = nullptr;
    IDXGIAdapter2 *_adapter2 = nullptr;
    IDXGIAdapter3 *_adapter3 = nullptr;
    IDXGIAdapter4 *_adapter4 = nullptr;

public:
    DXGIAdapterProxy(IDXGIAdapter *adapter) : _adapter(adapter)
    {
    }
    DXGIAdapterProxy(IDXGIAdapter1 *adapter) : _adapter(adapter), _adapter1(adapter)
    {
    }
    DXGIAdapterProxy(IDXGIAdapter2 *adapter) : _adapter(adapter), _adapter1(adapter), _adapter2(adapter)
    {
    }
    DXGIAdapterProxy(IDXGIAdapter3 *adapter) : _adapter(adapter), _adapter1(adapter), _adapter2(adapter), _adapter3(adapter)
    {
    }
    DXGIAdapterProxy(IDXGIAdapter4 *adapter) : _adapter(adapter), _adapter1(adapter), _adapter2(adapter), _adapter3(adapter), _adapter4(adapter)
    {
    }

    // Inherited via IDXGIAdapter4
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;
    virtual HRESULT STDMETHODCALLTYPE EnumOutputs(UINT Output, IDXGIOutput **ppOutput) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_ADAPTER_DESC *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER *pUMDVersion) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_ADAPTER_DESC1 *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc2(DXGI_ADAPTER_DESC2 *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD *pdwCookie) override;
    virtual void STDMETHODCALLTYPE UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO *pVideoMemoryInfo) override;
    virtual HRESULT STDMETHODCALLTYPE SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD *pdwCookie) override;
    virtual void STDMETHODCALLTYPE UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc3(DXGI_ADAPTER_DESC3 *pDesc) override;
};
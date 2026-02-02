#pragma once
#include <dxgi1_6.h>
#include "../utils.h"

class DXGISwapChainProxy : public IDXGISwapChain4
{
    IDXGISwapChain *_swapChain = nullptr;
    IDXGISwapChain1 *_swapChain1 = nullptr;
    IDXGISwapChain2 *_swapChain2 = nullptr;
    IDXGISwapChain3 *_swapChain3 = nullptr;
    IDXGISwapChain4 *_swapChain4 = nullptr;

    bool _handleD3D12MaximumFrameLatency = false;
    HANDLE _frameLatencyWaitHandle = NULL;

public:
    DXGISwapChainProxy(IDXGISwapChain *swapChain) : _swapChain(swapChain)
    {
    }
    DXGISwapChainProxy(IDXGISwapChain1 *swapChain) : _swapChain(swapChain), _swapChain1(swapChain)
    {
    }
    DXGISwapChainProxy(IDXGISwapChain2 *swapChain) : _swapChain(swapChain), _swapChain1(swapChain), _swapChain2(swapChain)
    {
    }
    DXGISwapChainProxy(IDXGISwapChain3 *swapChain) : _swapChain(swapChain), _swapChain1(swapChain), _swapChain2(swapChain), _swapChain3(swapChain)
    {
    }
    DXGISwapChainProxy(IDXGISwapChain4 *swapChain) : _swapChain(swapChain), _swapChain1(swapChain), _swapChain2(swapChain), _swapChain3(swapChain), _swapChain4(swapChain)
    {
    }

    static inline void QueryProxy(REFIID riid, void **ppvObject, DXGISwapChainProxy *pCurrent)
    {
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain1>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain2>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain3>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain4>(riid, ppvObject);
        proxyHelper.AndThankYou(riid, ppvObject);
        if (proxyHelper.UwU() && pCurrent)
        {
            ((DXGISwapChainProxy *)*ppvObject)->_handleD3D12MaximumFrameLatency = pCurrent->_handleD3D12MaximumFrameLatency;
            ((DXGISwapChainProxy *)*ppvObject)->_frameLatencyWaitHandle = pCurrent->_frameLatencyWaitHandle;
        }
    }

    void EnableD3D12MaximumFrameLatencyHandling();
    void ApplyMaximumFrameLatency();

    // Inherited via IDXGISwapChain2
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;
    virtual HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppDevice) override;
    virtual HRESULT STDMETHODCALLTYPE Present(UINT SyncInterval, UINT Flags) override;
    virtual HRESULT STDMETHODCALLTYPE GetBuffer(UINT Buffer, REFIID riid, void **ppSurface) override;
    virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget) override;
    virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) override;
    virtual HRESULT STDMETHODCALLTYPE ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters) override;
    virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(IDXGIOutput **ppOutput) override;
    virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats) override;
    virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(UINT *pLastPresentCount) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE GetHwnd(HWND *pHwnd) override;
    virtual HRESULT STDMETHODCALLTYPE GetCoreWindow(REFIID refiid, void **ppUnk) override;
    virtual HRESULT STDMETHODCALLTYPE Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters) override;
    virtual BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported(void) override;
    virtual HRESULT STDMETHODCALLTYPE GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput) override;
    virtual HRESULT STDMETHODCALLTYPE SetBackgroundColor(const DXGI_RGBA *pColor) override;
    virtual HRESULT STDMETHODCALLTYPE GetBackgroundColor(DXGI_RGBA *pColor) override;
    virtual HRESULT STDMETHODCALLTYPE SetRotation(DXGI_MODE_ROTATION Rotation) override;
    virtual HRESULT STDMETHODCALLTYPE GetRotation(DXGI_MODE_ROTATION *pRotation) override;
    virtual HRESULT STDMETHODCALLTYPE SetSourceSize(UINT Width, UINT Height) override;
    virtual HRESULT STDMETHODCALLTYPE GetSourceSize(UINT *pWidth, UINT *pHeight) override;
    virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency) override;
    virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT *pMaxLatency) override;
    virtual HANDLE STDMETHODCALLTYPE GetFrameLatencyWaitableObject(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetMatrixTransform(const DXGI_MATRIX_3X2_F *pMatrix) override;
    virtual HRESULT STDMETHODCALLTYPE GetMatrixTransform(DXGI_MATRIX_3X2_F *pMatrix) override;
    virtual UINT STDMETHODCALLTYPE GetCurrentBackBufferIndex(void) override;
    virtual HRESULT STDMETHODCALLTYPE CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT *pColorSpaceSupport) override;
    virtual HRESULT STDMETHODCALLTYPE SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace) override;
    virtual HRESULT STDMETHODCALLTYPE ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT *pCreationNodeMask, IUnknown *const *ppPresentQueue) override;
    virtual HRESULT STDMETHODCALLTYPE SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void *pMetaData) override;
};
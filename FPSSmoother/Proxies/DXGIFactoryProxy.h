#pragma once
#include <dxgi1_6.h>

class DXGIFactoryProxy : public IDXGIFactory7
{
    IDXGIFactory *_factory = nullptr;
    IDXGIFactory1 *_factory1 = nullptr;
    IDXGIFactory2 *_factory2 = nullptr;
    IDXGIFactory3 *_factory3 = nullptr;
    IDXGIFactory4 *_factory4 = nullptr;
    IDXGIFactory5 *_factory5 = nullptr;
    IDXGIFactory6 *_factory6 = nullptr;
    IDXGIFactory7 *_factory7 = nullptr;

public:
    DXGIFactoryProxy(IDXGIFactory *factory) : _factory(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory1 *factory) : _factory(factory), _factory1(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory2 *factory) : _factory(factory), _factory1(factory), _factory2(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory3 *factory) : _factory(factory), _factory1(factory), _factory2(factory), _factory3(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory4 *factory) : _factory(factory), _factory1(factory), _factory2(factory), _factory3(factory), _factory4(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory5 *factory) : _factory(factory), _factory1(factory), _factory2(factory), _factory3(factory), _factory4(factory), _factory5(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory6 *factory) : _factory(factory), _factory1(factory), _factory2(factory), _factory3(factory), _factory4(factory), _factory5(factory), _factory6(factory)
    {
    }
    DXGIFactoryProxy(IDXGIFactory7 *factory) : _factory(factory), _factory1(factory), _factory2(factory), _factory3(factory), _factory4(factory), _factory5(factory), _factory6(factory), _factory7(factory)
    {
    }

    // Inherited via IDXGIFactory7
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;
    virtual HRESULT STDMETHODCALLTYPE EnumAdapters(UINT Adapter, IDXGIAdapter **ppAdapter) override;
    virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation(HWND WindowHandle, UINT Flags) override;
    virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation(HWND *pWindowHandle) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC *pDesc, IDXGISwapChain **ppSwapChain) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter **ppAdapter) override;
    virtual HRESULT STDMETHODCALLTYPE EnumAdapters1(UINT Adapter, IDXGIAdapter1 **ppAdapter) override;
    virtual BOOL STDMETHODCALLTYPE IsCurrent(void) override;
    virtual BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled(void) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(IUnknown *pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1 *pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(IUnknown *pDevice, IUnknown *pWindow, const DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain) override;
    virtual HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(HANDLE hResource, LUID *pLuid) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(HANDLE hEvent, DWORD *pdwCookie) override;
    virtual void STDMETHODCALLTYPE UnregisterStereoStatus(DWORD dwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD *pdwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD *pdwCookie) override;
    virtual void STDMETHODCALLTYPE UnregisterOcclusionStatus(DWORD dwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(IUnknown *pDevice, const DXGI_SWAP_CHAIN_DESC1 *pDesc, IDXGIOutput *pRestrictToOutput, IDXGISwapChain1 **ppSwapChain) override;
    virtual UINT STDMETHODCALLTYPE GetCreationFlags(void) override;
    virtual HRESULT STDMETHODCALLTYPE EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void **ppvAdapter) override;
    virtual HRESULT STDMETHODCALLTYPE EnumWarpAdapter(REFIID riid, void **ppvAdapter) override;
    virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(DXGI_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize) override;
    virtual HRESULT STDMETHODCALLTYPE EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void **ppvAdapter) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterAdaptersChangedEvent(HANDLE hEvent, DWORD *pdwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE UnregisterAdaptersChangedEvent(DWORD dwCookie) override;
};
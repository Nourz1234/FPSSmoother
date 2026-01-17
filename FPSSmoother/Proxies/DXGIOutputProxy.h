#pragma once
#include <d3d11_2.h>

class DXGIOutputProxy : public IDXGIOutput
{
    IDXGIOutput* _output = nullptr;
    ULONG m_RefCount = 0;
public:
    DXGIOutputProxy(IDXGIOutput* output) : _output(output)
    {
        m_RefCount = 1;
    }
    ~DXGIOutputProxy()
    {
        _output->Release();
    }

    // Inherited via IDXGIOutput
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void * pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void ** ppParent) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_OUTPUT_DESC * pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT * pNumModes, DXGI_MODE_DESC * pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE FindClosestMatchingMode(const DXGI_MODE_DESC * pModeToMatch, DXGI_MODE_DESC * pClosestMatch, IUnknown * pConcernedDevice) override;
    virtual HRESULT STDMETHODCALLTYPE WaitForVBlank(void) override;
    virtual HRESULT STDMETHODCALLTYPE TakeOwnership(IUnknown * pDevice, BOOL Exclusive) override;
    virtual void STDMETHODCALLTYPE ReleaseOwnership(void) override;
    virtual HRESULT STDMETHODCALLTYPE GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES * pGammaCaps) override;
    virtual HRESULT STDMETHODCALLTYPE SetGammaControl(const DXGI_GAMMA_CONTROL * pArray) override;
    virtual HRESULT STDMETHODCALLTYPE GetGammaControl(DXGI_GAMMA_CONTROL * pArray) override;
    virtual HRESULT STDMETHODCALLTYPE SetDisplaySurface(IDXGISurface * pScanoutSurface) override;
    virtual HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData(IDXGISurface * pDestination) override;
    virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS * pStats) override;
};
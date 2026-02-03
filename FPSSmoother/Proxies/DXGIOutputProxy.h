#pragma once
#include <dxgi1_6.h>
#include "ProxyBase.h"

class DXGIOutputProxy : public IDXGIOutput6, public ProxyBase
{
    IDXGIOutput *_output = nullptr;
    IDXGIOutput1 *_output1 = nullptr;
    IDXGIOutput2 *_output2 = nullptr;
    IDXGIOutput3 *_output3 = nullptr;
    IDXGIOutput4 *_output4 = nullptr;
    IDXGIOutput5 *_output5 = nullptr;
    IDXGIOutput6 *_output6 = nullptr;

public:
    DXGIOutputProxy(IDXGIOutput *output) : _output(output)
    {
    }
    DXGIOutputProxy(IDXGIOutput1 *output) : _output(output), _output1(output)
    {
    }
    DXGIOutputProxy(IDXGIOutput2 *output) : _output(output), _output1(output), _output2(output)
    {
    }
    DXGIOutputProxy(IDXGIOutput3 *output) : _output(output), _output1(output), _output2(output), _output3(output)
    {
    }
    DXGIOutputProxy(IDXGIOutput4 *output) : _output(output), _output1(output), _output2(output), _output3(output), _output4(output)
    {
    }
    DXGIOutputProxy(IDXGIOutput5 *output) : _output(output), _output1(output), _output2(output), _output3(output), _output4(output), _output5(output)
    {
    }
    DXGIOutputProxy(IDXGIOutput6 *output) : _output(output), _output1(output), _output2(output), _output3(output), _output4(output), _output5(output), _output6(output)
    {
    }

    virtual void CopyTo(ProxyBase *other) override {}

    // Inherited via IDXGIOutput6
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData) override;
    virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void **ppParent) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_OUTPUT_DESC *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc) override;
    virtual HRESULT STDMETHODCALLTYPE FindClosestMatchingMode(const DXGI_MODE_DESC *pModeToMatch, DXGI_MODE_DESC *pClosestMatch, IUnknown *pConcernedDevice) override;
    virtual HRESULT STDMETHODCALLTYPE WaitForVBlank(void) override;
    virtual HRESULT STDMETHODCALLTYPE TakeOwnership(IUnknown *pDevice, BOOL Exclusive) override;
    virtual void STDMETHODCALLTYPE ReleaseOwnership(void) override;
    virtual HRESULT STDMETHODCALLTYPE GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps) override;
    virtual HRESULT STDMETHODCALLTYPE SetGammaControl(const DXGI_GAMMA_CONTROL *pArray) override;
    virtual HRESULT STDMETHODCALLTYPE GetGammaControl(DXGI_GAMMA_CONTROL *pArray) override;
    virtual HRESULT STDMETHODCALLTYPE SetDisplaySurface(IDXGISurface *pScanoutSurface) override;
    virtual HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData(IDXGISurface *pDestination) override;
    virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats) override;
    virtual HRESULT STDMETHODCALLTYPE GetDisplayModeList1(DXGI_FORMAT enum_format, UINT flags, UINT *num_modes, DXGI_MODE_DESC1 *desc) override;
    virtual HRESULT STDMETHODCALLTYPE FindClosestMatchingMode1(const DXGI_MODE_DESC1 *mode_to_match, DXGI_MODE_DESC1 *closest_match, IUnknown *concerned_device) override;
    virtual HRESULT STDMETHODCALLTYPE GetDisplaySurfaceData1(IDXGIResource *destination) override;
    virtual HRESULT STDMETHODCALLTYPE DuplicateOutput(IUnknown *device, IDXGIOutputDuplication **output_duplication) override;
    virtual WINBOOL STDMETHODCALLTYPE SupportsOverlays() override;
    virtual HRESULT STDMETHODCALLTYPE CheckOverlaySupport(DXGI_FORMAT enum_format, IUnknown *concerned_device, UINT *flags) override;
    virtual HRESULT STDMETHODCALLTYPE CheckOverlayColorSpaceSupport(DXGI_FORMAT format, DXGI_COLOR_SPACE_TYPE colour_space, IUnknown *device, UINT *flags) override;
    virtual HRESULT STDMETHODCALLTYPE DuplicateOutput1(IUnknown *device, UINT flags, UINT format_count, const DXGI_FORMAT *formats, IDXGIOutputDuplication **duplication) override;
    virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_OUTPUT_DESC1 *desc) override;
    virtual HRESULT STDMETHODCALLTYPE CheckHardwareCompositionSupport(UINT *flags) override;
};
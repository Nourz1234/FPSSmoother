#include "DXGIOutputProxy.h"
#include "../globals.h"
#include "../utils.h"

HRESULT DXGIOutputProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"DXGIOutputProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _output->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        DXGIOutputProxy::QueryProxy(riid, ppvObject);
    }

    return hr;
}

ULONG DXGIOutputProxy::AddRef(void)
{
    return _output->AddRef();
}

ULONG DXGIOutputProxy::Release(void)
{
    return _output->Release();
}

HRESULT DXGIOutputProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
    return _output->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIOutputProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
    return _output->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIOutputProxy::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
    return _output->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIOutputProxy::GetParent(REFIID riid, void **ppParent)
{
    inc_dbg_level(L"DXGIOutputProxy::GetParent");

    return _output->GetParent(riid, ppParent);
}

HRESULT DXGIOutputProxy::GetDesc(DXGI_OUTPUT_DESC *pDesc)
{
    return _output->GetDesc(pDesc);
}

HRESULT DXGIOutputProxy::GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT *pNumModes, DXGI_MODE_DESC *pDesc)
{
    return _output->GetDisplayModeList(EnumFormat, Flags, pNumModes, pDesc);
}

HRESULT DXGIOutputProxy::FindClosestMatchingMode(const DXGI_MODE_DESC *pModeToMatch, DXGI_MODE_DESC *pClosestMatch, IUnknown *pConcernedDevice)
{
    return _output->FindClosestMatchingMode(pModeToMatch, pClosestMatch, pConcernedDevice);
}

HRESULT DXGIOutputProxy::WaitForVBlank(void)
{
    return _output->WaitForVBlank();
}

HRESULT DXGIOutputProxy::TakeOwnership(IUnknown *pDevice, BOOL Exclusive)
{
    return _output->TakeOwnership(pDevice, Exclusive);
}

void DXGIOutputProxy::ReleaseOwnership(void)
{
    _output->ReleaseOwnership();
}

HRESULT DXGIOutputProxy::GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES *pGammaCaps)
{
    return _output->GetGammaControlCapabilities(pGammaCaps);
}

HRESULT DXGIOutputProxy::SetGammaControl(const DXGI_GAMMA_CONTROL *pArray)
{
    return _output->SetGammaControl(pArray);
}

HRESULT DXGIOutputProxy::GetGammaControl(DXGI_GAMMA_CONTROL *pArray)
{
    return _output->GetGammaControl(pArray);
}

HRESULT DXGIOutputProxy::SetDisplaySurface(IDXGISurface *pScanoutSurface)
{
    inc_dbg_level(L"DXGIOutputProxy::SetDisplaySurface");

    return _output->SetDisplaySurface(pScanoutSurface);
}

HRESULT DXGIOutputProxy::GetDisplaySurfaceData(IDXGISurface *pDestination)
{
    inc_dbg_level(L"DXGIOutputProxy::GetDisplaySurfaceData");

    return _output->GetDisplaySurfaceData(pDestination);
}

HRESULT DXGIOutputProxy::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
{
    return _output->GetFrameStatistics(pStats);
}

HRESULT DXGIOutputProxy::GetDisplayModeList1(DXGI_FORMAT enum_format, UINT flags, UINT *num_modes, DXGI_MODE_DESC1 *desc)
{
    if (_output1)
        return _output1->GetDisplayModeList1(enum_format, flags, num_modes, desc);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::FindClosestMatchingMode1(const DXGI_MODE_DESC1 *mode_to_match, DXGI_MODE_DESC1 *closest_match, IUnknown *concerned_device)
{
    if (_output1)
        return _output1->FindClosestMatchingMode1(mode_to_match, closest_match, concerned_device);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::GetDisplaySurfaceData1(IDXGIResource *destination)
{
    inc_dbg_level(L"DXGIOutputProxy::GetDisplaySurfaceData1");

    if (_output1)
        return _output1->GetDisplaySurfaceData1(destination);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::DuplicateOutput(IUnknown *device, IDXGIOutputDuplication **output_duplication)
{
    inc_dbg_level(L"DXGIOutputProxy::DuplicateOutput");

    if (_output1)
        return _output1->DuplicateOutput(device, output_duplication);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

WINBOOL DXGIOutputProxy::SupportsOverlays()
{
    if (_output2)
        return _output2->SupportsOverlays();

    debug(L"Warning: Not implemented code path reached.");
    return FALSE;
}

HRESULT DXGIOutputProxy::CheckOverlaySupport(DXGI_FORMAT enum_format, IUnknown *concerned_device, UINT *flags)
{
    if (_output3)
        return _output3->CheckOverlaySupport(enum_format, concerned_device, flags);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::CheckOverlayColorSpaceSupport(DXGI_FORMAT format, DXGI_COLOR_SPACE_TYPE colour_space, IUnknown *device, UINT *flags)
{
    if (_output4)
        return _output4->CheckOverlayColorSpaceSupport(format, colour_space, device, flags);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::DuplicateOutput1(IUnknown *device, UINT flags, UINT format_count, const DXGI_FORMAT *formats, IDXGIOutputDuplication **duplication)
{
    inc_dbg_level(L"DXGIOutputProxy::DuplicateOutput1");

    if (_output5)
        return _output5->DuplicateOutput1(device, flags, format_count, formats, duplication);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::GetDesc1(DXGI_OUTPUT_DESC1 *desc)
{
    if (_output6)
        return _output6->GetDesc1(desc);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT DXGIOutputProxy::CheckHardwareCompositionSupport(UINT *flags)
{
    if (_output6)
        return _output6->CheckHardwareCompositionSupport(flags);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

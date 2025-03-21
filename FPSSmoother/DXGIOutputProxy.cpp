#include "DXGIOutputProxy.h"
#include "Util.h"


HRESULT DXGIOutputProxy::QueryInterface(REFIID riid, void ** ppvObject)
{
    HRESULT hr = _output->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        if (IsEqualIID(riid, __uuidof(IDXGIOutput)))
        {
            *ppvObject = static_cast<IDXGIOutput*>(new DXGIOutputProxy((IDXGIOutput*)*ppvObject));
        }
        else
        {
            LPOLESTR pIID = 0;
            StringFromCLSID(riid, &pIID);
            // msgbox(L"DXGIOutputProxy::QueryInterface: %s", pIID);
        }
    }

    return hr;
}

ULONG DXGIOutputProxy::AddRef(void)
{
    return InterlockedIncrement(&m_RefCount);
}

ULONG DXGIOutputProxy::Release(void)
{
    ULONG count = InterlockedDecrement(&m_RefCount);
    if (count == 0) delete this;
    return count;
}

HRESULT DXGIOutputProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void * pData)
{
    return _output->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGIOutputProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown * pUnknown)
{
    return _output->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGIOutputProxy::GetPrivateData(REFGUID Name, UINT * pDataSize, void * pData)
{
    return _output->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGIOutputProxy::GetParent(REFIID riid, void ** ppParent)
{
    LPOLESTR pIID = 0;
    StringFromCLSID(riid, &pIID);
    // msgbox(L"DXGIOutputProxy::GetParent: %s", pIID);

    return _output->GetParent(riid, ppParent);
}

HRESULT DXGIOutputProxy::GetDesc(DXGI_OUTPUT_DESC * pDesc)
{
    return _output->GetDesc(pDesc);
}

HRESULT DXGIOutputProxy::GetDisplayModeList(DXGI_FORMAT EnumFormat, UINT Flags, UINT * pNumModes, DXGI_MODE_DESC * pDesc)
{
    return _output->GetDisplayModeList(EnumFormat, Flags, pNumModes, pDesc);
}

HRESULT DXGIOutputProxy::FindClosestMatchingMode(const DXGI_MODE_DESC * pModeToMatch, DXGI_MODE_DESC * pClosestMatch, IUnknown * pConcernedDevice)
{
    return _output->FindClosestMatchingMode(pModeToMatch, pClosestMatch, pConcernedDevice);
}

HRESULT DXGIOutputProxy::WaitForVBlank(void)
{
    // msgbox(L"DXGIOutputProxy::WaitForVBlank");
    return _output->WaitForVBlank();
}

HRESULT DXGIOutputProxy::TakeOwnership(IUnknown * pDevice, BOOL Exclusive)
{
    // msgbox(L"DXGIOutputProxy::TakeOwnership");
    return _output->TakeOwnership(pDevice, Exclusive);
}

void DXGIOutputProxy::ReleaseOwnership(void)
{
    _output->ReleaseOwnership();
}

HRESULT DXGIOutputProxy::GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES * pGammaCaps)
{
    return _output->GetGammaControlCapabilities(pGammaCaps);
}

HRESULT DXGIOutputProxy::SetGammaControl(const DXGI_GAMMA_CONTROL * pArray)
{
    return _output->SetGammaControl(pArray);
}

HRESULT DXGIOutputProxy::GetGammaControl(DXGI_GAMMA_CONTROL * pArray)
{
    return _output->GetGammaControl(pArray);
}

HRESULT DXGIOutputProxy::SetDisplaySurface(IDXGISurface * pScanoutSurface)
{
    return _output->SetDisplaySurface(pScanoutSurface);
}

HRESULT DXGIOutputProxy::GetDisplaySurfaceData(IDXGISurface * pDestination)
{
    return _output->GetDisplaySurfaceData(pDestination);
}

HRESULT DXGIOutputProxy::GetFrameStatistics(DXGI_FRAME_STATISTICS * pStats)
{
    return _output->GetFrameStatistics(pStats);
}

#include "DXGISwapChainProxy.h"
#include "Util.h"
#include "globals.h"

void nanosleep(LONGLONG ns)
{
    /* Declarations */
    static HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
    static LARGE_INTEGER li;

    /* Set timer properties */
    li.QuadPart = -(ns / 100);
    SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE);
    WaitForSingleObjectEx(timer, INFINITE, TRUE);
}

void syncFrame()
{
    static LARGE_INTEGER lastCounter{};
    static LARGE_INTEGER counter;
    static long double msFrequency = 0;
    static long double msElapsed;
    static long double msFrameTime = 1000.0L / g_FPSLimit;

    if (!msFrequency)
    {
        LARGE_INTEGER f{};
        QueryPerformanceFrequency(&f);
        msFrequency = f.QuadPart / 1000.0L;
    }

    QueryPerformanceCounter(&counter);
    if (!lastCounter.QuadPart)
    {
        lastCounter = counter;
        return;
    }
    msElapsed = (counter.QuadPart - lastCounter.QuadPart) / msFrequency;
    // debug(L"-> elapsedMilliseconds: %Lf", elapsedMilliseconds);

    if (msElapsed < msFrameTime)
    {
        nanosleep((msFrameTime - msElapsed) * 1000000);
        QueryPerformanceCounter(&lastCounter);
    }
    else
    {
        lastCounter = counter;
    }
}

HRESULT DXGISwapChainProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"DXGISwapChainProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _swapChain->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        ProxyHelper proxyHelper;
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain1>(riid, ppvObject);
        proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain2>(riid, ppvObject);
        proxyHelper.AndThankYou(riid, ppvObject);
    }

    return hr;
}

ULONG DXGISwapChainProxy::AddRef(void)
{
    inc_dbg_level(L"DXGISwapChainProxy::AddRef");

    return _swapChain->AddRef();
}

ULONG DXGISwapChainProxy::Release(void)
{
    inc_dbg_level(L"DXGISwapChainProxy::Release");

    return _swapChain->Release();
}

HRESULT DXGISwapChainProxy::SetPrivateData(REFGUID Name, UINT DataSize, const void *pData)
{
    return _swapChain->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGISwapChainProxy::SetPrivateDataInterface(REFGUID Name, const IUnknown *pUnknown)
{
    return _swapChain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGISwapChainProxy::GetPrivateData(REFGUID Name, UINT *pDataSize, void *pData)
{
    return _swapChain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGISwapChainProxy::GetParent(REFIID riid, void **ppParent)
{
    inc_dbg_level(L"DXGISwapChainProxy::GetParent");

    return _swapChain->GetParent(riid, ppParent);
}

HRESULT DXGISwapChainProxy::GetDevice(REFIID riid, void **ppDevice)
{
    return _swapChain->GetDevice(riid, ppDevice);
}

HRESULT DXGISwapChainProxy::Present(UINT SyncInterval, UINT Flags)
{
    if (g_SetAllowTearing)
    {
        if (g_AllowTearing)
            Flags |= DXGI_PRESENT_ALLOW_TEARING;
        else
            Flags &= ~DXGI_PRESENT_ALLOW_TEARING;
    }
    if (g_SetSyncInterval)
    {
        SyncInterval = g_SyncInterval;
        if (g_SyncInterval > 0)
            Flags &= ~DXGI_PRESENT_ALLOW_TEARING;
    }
    if (g_SetFPSLimit)
        syncFrame();

    return _swapChain->Present(SyncInterval, Flags);
}

HRESULT DXGISwapChainProxy::GetBuffer(UINT Buffer, REFIID riid, void **ppSurface)
{
    return _swapChain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT DXGISwapChainProxy::SetFullscreenState(BOOL Fullscreen, IDXGIOutput *pTarget)
{
    inc_dbg_level(L"DXGISwapChainProxy::SetFullscreenState");

    debug(L"-> Fullscreen: %d", Fullscreen);
    return _swapChain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT DXGISwapChainProxy::GetFullscreenState(BOOL *pFullscreen, IDXGIOutput **ppTarget)
{
    return _swapChain->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT DXGISwapChainProxy::GetDesc(DXGI_SWAP_CHAIN_DESC *pDesc)
{
    return _swapChain->GetDesc(pDesc);
}

HRESULT DXGISwapChainProxy::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
    inc_dbg_level(L"DXGISwapChainProxy::ResizeBuffers");

    if (g_SetSwapChainBufferCount)
        BufferCount = g_SwapChainBufferCount;
    if (g_SetAllowTearing)
    {
        if (g_AllowTearing)
            SwapChainFlags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
        else
            SwapChainFlags &= ~DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    }

    debug(L"-> BufferCount: %d Size: %dx%d", BufferCount, Width, Height);
    return _swapChain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT DXGISwapChainProxy::ResizeTarget(const DXGI_MODE_DESC *pNewTargetParameters)
{
    inc_dbg_level(L"DXGISwapChainProxy::ResizeTarget");

    if (g_SetPreferredRefreshRate)
        ((DXGI_MODE_DESC *)pNewTargetParameters)->RefreshRate.Numerator = g_PreferredRefreshRate;

    debug(
        L"-> Mode: %dx%d RefreshRate: %d",
        pNewTargetParameters->Width,
        pNewTargetParameters->Height,
        pNewTargetParameters->RefreshRate.Numerator);
    return _swapChain->ResizeTarget(pNewTargetParameters);
}

HRESULT DXGISwapChainProxy::GetContainingOutput(IDXGIOutput **ppOutput)
{
    // inc_dbg_level(L"DXGISwapChainProxy::GetContainingOutput");

    return _swapChain->GetContainingOutput(ppOutput);
}

HRESULT DXGISwapChainProxy::GetFrameStatistics(DXGI_FRAME_STATISTICS *pStats)
{
    return _swapChain->GetFrameStatistics(pStats);
}

HRESULT DXGISwapChainProxy::GetLastPresentCount(UINT *pLastPresentCount)
{
    return _swapChain->GetLastPresentCount(pLastPresentCount);
}

HRESULT DXGISwapChainProxy::GetDesc1(DXGI_SWAP_CHAIN_DESC1 *pDesc)
{
    if (_swapChain1)
        return _swapChain1->GetDesc1(pDesc);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc)
{
    if (_swapChain1)
        return _swapChain1->GetFullscreenDesc(pDesc);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetHwnd(HWND *pHwnd)
{
    if (_swapChain1)
        return _swapChain1->GetHwnd(pHwnd);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetCoreWindow(REFIID refiid, void **ppUnk)
{
    if (_swapChain1)
        return _swapChain1->GetCoreWindow(refiid, ppUnk);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters)
{
    if (_swapChain1)
    {
        if (g_SetAllowTearing)
        {
            if (g_AllowTearing)
                PresentFlags |= DXGI_PRESENT_ALLOW_TEARING;
            else
                PresentFlags &= ~DXGI_PRESENT_ALLOW_TEARING;
        }
        if (g_SetSyncInterval)
        {
            SyncInterval = g_SyncInterval;
            if (g_SyncInterval > 0)
                PresentFlags &= ~DXGI_PRESENT_ALLOW_TEARING;
        }
        if (g_SetFPSLimit)
            syncFrame();

        return _swapChain1->Present1(SyncInterval, PresentFlags, pPresentParameters);
    }
    return E_NOTIMPL;
}

BOOL DXGISwapChainProxy::IsTemporaryMonoSupported(void)
{
    if (_swapChain1)
        return _swapChain1->IsTemporaryMonoSupported();
    return FALSE;
}

HRESULT DXGISwapChainProxy::GetRestrictToOutput(IDXGIOutput **ppRestrictToOutput)
{
    return _swapChain1->GetRestrictToOutput(ppRestrictToOutput);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::SetBackgroundColor(const DXGI_RGBA *pColor)
{
    if (_swapChain1)
        return _swapChain1->SetBackgroundColor(pColor);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetBackgroundColor(DXGI_RGBA *pColor)
{
    if (_swapChain1)
        return _swapChain1->GetBackgroundColor(pColor);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::SetRotation(DXGI_MODE_ROTATION Rotation)
{
    if (_swapChain1)
        return _swapChain1->SetRotation(Rotation);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetRotation(DXGI_MODE_ROTATION *pRotation)
{
    if (_swapChain1)
        return _swapChain1->GetRotation(pRotation);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::SetSourceSize(UINT Width, UINT Height)
{
    if (_swapChain2)
        return _swapChain2->SetSourceSize(Width, Height);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetSourceSize(UINT *pWidth, UINT *pHeight)
{
    if (_swapChain2)
        return _swapChain2->GetSourceSize(pWidth, pHeight);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::SetMaximumFrameLatency(UINT MaxLatency)
{
    inc_dbg_level(L"DXGISwapChainProxy::SetMaximumFrameLatency");

    if (_swapChain2)
    {
        debug(L"-> MaxLatency: %d", MaxLatency);
        return _swapChain2->SetMaximumFrameLatency(MaxLatency);
    }

    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetMaximumFrameLatency(UINT *pMaxLatency)
{
    if (_swapChain2)
        return _swapChain2->GetMaximumFrameLatency(pMaxLatency);
    return E_NOTIMPL;
}

HANDLE DXGISwapChainProxy::GetFrameLatencyWaitableObject(void)
{
    if (_swapChain2)
        return _swapChain2->GetFrameLatencyWaitableObject();
    return NULL;
}

HRESULT DXGISwapChainProxy::SetMatrixTransform(const DXGI_MATRIX_3X2_F *pMatrix)
{
    if (_swapChain2)
        return _swapChain2->SetMatrixTransform(pMatrix);
    return E_NOTIMPL;
}

HRESULT DXGISwapChainProxy::GetMatrixTransform(DXGI_MATRIX_3X2_F *pMatrix)
{
    if (_swapChain2)
        return _swapChain2->GetMatrixTransform(pMatrix);
    return E_NOTIMPL;
}

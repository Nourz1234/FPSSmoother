#include "D3D11DeviceProxy.h"
#include "../globals.h"
#include "../utils.h"
#include "../proxy_utils.h"

HRESULT D3D11DeviceProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"D3D11DeviceProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _device->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppvObject, this);
    }

    return hr;
}

ULONG D3D11DeviceProxy::AddRef(void)
{
    inc_dbg_level(L"D3D11DeviceProxy::AddRef");

    return _device->AddRef();
}

ULONG D3D11DeviceProxy::Release(void)
{
    inc_dbg_level(L"D3D11DeviceProxy::Release");

    return _device->Release();
}

HRESULT D3D11DeviceProxy::CreateBuffer(const D3D11_BUFFER_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Buffer **ppBuffer)
{
    return _device->CreateBuffer(pDesc, pInitialData, ppBuffer);
}

HRESULT D3D11DeviceProxy::CreateTexture1D(const D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture1D **ppTexture1D)
{
    return _device->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
}

HRESULT D3D11DeviceProxy::CreateTexture2D(const D3D11_TEXTURE2D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D)
{
    return _device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}

HRESULT D3D11DeviceProxy::CreateTexture3D(const D3D11_TEXTURE3D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture3D **ppTexture3D)
{
    return _device->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
}

HRESULT D3D11DeviceProxy::CreateShaderResourceView(ID3D11Resource *pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11ShaderResourceView **ppSRView)
{
    return _device->CreateShaderResourceView(pResource, pDesc, ppSRView);
}

HRESULT D3D11DeviceProxy::CreateUnorderedAccessView(ID3D11Resource *pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, ID3D11UnorderedAccessView **ppUAView)
{
    return _device->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
}

HRESULT D3D11DeviceProxy::CreateRenderTargetView(ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView **ppRTView)
{
    return _device->CreateRenderTargetView(pResource, pDesc, ppRTView);
}

HRESULT D3D11DeviceProxy::CreateDepthStencilView(ID3D11Resource *pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, ID3D11DepthStencilView **ppDepthStencilView)
{
    return _device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}

HRESULT D3D11DeviceProxy::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout **ppInputLayout)
{
    return _device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}

HRESULT D3D11DeviceProxy::CreateVertexShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader)
{
    return _device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

HRESULT D3D11DeviceProxy::CreateGeometryShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader)
{
    return _device->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
}

HRESULT D3D11DeviceProxy::CreateGeometryShaderWithStreamOutput(const void *pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries, const UINT *pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader)
{
    return _device->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
}

HRESULT D3D11DeviceProxy::CreatePixelShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader)
{
    return _device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}

HRESULT D3D11DeviceProxy::CreateHullShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11HullShader **ppHullShader)
{
    return _device->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
}

HRESULT D3D11DeviceProxy::CreateDomainShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11DomainShader **ppDomainShader)
{
    return _device->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
}

HRESULT D3D11DeviceProxy::CreateComputeShader(const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11ComputeShader **ppComputeShader)
{
    return _device->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
}

HRESULT D3D11DeviceProxy::CreateClassLinkage(ID3D11ClassLinkage **ppLinkage)
{
    return _device->CreateClassLinkage(ppLinkage);
}

HRESULT D3D11DeviceProxy::CreateBlendState(const D3D11_BLEND_DESC *pBlendStateDesc, ID3D11BlendState **ppBlendState)
{
    return _device->CreateBlendState(pBlendStateDesc, ppBlendState);
}

HRESULT D3D11DeviceProxy::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc, ID3D11DepthStencilState **ppDepthStencilState)
{
    return _device->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
}

HRESULT D3D11DeviceProxy::CreateRasterizerState(const D3D11_RASTERIZER_DESC *pRasterizerDesc, ID3D11RasterizerState **ppRasterizerState)
{
    return _device->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}

HRESULT D3D11DeviceProxy::CreateSamplerState(const D3D11_SAMPLER_DESC *pSamplerDesc, ID3D11SamplerState **ppSamplerState)
{
    return _device->CreateSamplerState(pSamplerDesc, ppSamplerState);
}

HRESULT D3D11DeviceProxy::CreateQuery(const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery)
{
    return _device->CreateQuery(pQueryDesc, ppQuery);
}

HRESULT D3D11DeviceProxy::CreatePredicate(const D3D11_QUERY_DESC *pPredicateDesc, ID3D11Predicate **ppPredicate)
{
    return _device->CreatePredicate(pPredicateDesc, ppPredicate);
}

HRESULT D3D11DeviceProxy::CreateCounter(const D3D11_COUNTER_DESC *pCounterDesc, ID3D11Counter **ppCounter)
{
    return _device->CreateCounter(pCounterDesc, ppCounter);
}

HRESULT D3D11DeviceProxy::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext **ppDeferredContext)
{
    return _device->CreateDeferredContext(ContextFlags, ppDeferredContext);
}

HRESULT D3D11DeviceProxy::OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void **ppResource)
{
    return _device->OpenSharedResource(hResource, ReturnedInterface, ppResource);
}

HRESULT D3D11DeviceProxy::CheckFormatSupport(DXGI_FORMAT Format, UINT *pFormatSupport)
{
    return _device->CheckFormatSupport(Format, pFormatSupport);
}

HRESULT D3D11DeviceProxy::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT *pNumQualityLevels)
{
    return _device->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}

void D3D11DeviceProxy::CheckCounterInfo(D3D11_COUNTER_INFO *pCounterInfo)
{
    _device->CheckCounterInfo(pCounterInfo);
}

HRESULT D3D11DeviceProxy::CheckCounter(const D3D11_COUNTER_DESC *pDesc, D3D11_COUNTER_TYPE *pType, UINT *pActiveCounters, LPSTR szName, UINT *pNameLength, LPSTR szUnits, UINT *pUnitsLength, LPSTR szDescription, UINT *pDescriptionLength)
{
    return _device->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
}

HRESULT D3D11DeviceProxy::CheckFeatureSupport(D3D11_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize)
{
    return _device->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT D3D11DeviceProxy::GetPrivateData(REFGUID guid, UINT *pDataSize, void *pData)
{
    return _device->GetPrivateData(guid, pDataSize, pData);
}

HRESULT D3D11DeviceProxy::SetPrivateData(REFGUID guid, UINT DataSize, const void *pData)
{
    return _device->SetPrivateData(guid, DataSize, pData);
}

HRESULT D3D11DeviceProxy::SetPrivateDataInterface(REFGUID guid, const IUnknown *pData)
{
    return _device->SetPrivateDataInterface(guid, pData);
}

D3D_FEATURE_LEVEL D3D11DeviceProxy::GetFeatureLevel(void)
{
    return _device->GetFeatureLevel();
}

UINT D3D11DeviceProxy::GetCreationFlags(void)
{
    return _device->GetCreationFlags();
}

HRESULT D3D11DeviceProxy::GetDeviceRemovedReason(void)
{
    return _device->GetDeviceRemovedReason();
}

void D3D11DeviceProxy::GetImmediateContext(ID3D11DeviceContext **ppImmediateContext)
{
    _device->GetImmediateContext(ppImmediateContext);
}

HRESULT D3D11DeviceProxy::SetExceptionMode(UINT RaiseFlags)
{
    return _device->SetExceptionMode(RaiseFlags);
}

UINT D3D11DeviceProxy::GetExceptionMode(void)
{
    return _device->GetExceptionMode();
}

void D3D11DeviceProxy::GetImmediateContext1(ID3D11DeviceContext1 **ppImmediateContext)
{
    if (_device1)
        _device1->GetImmediateContext1(ppImmediateContext);
}

HRESULT D3D11DeviceProxy::CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1 **ppDeferredContext)
{
    if (_device1)
        _device1->CreateDeferredContext1(ContextFlags, ppDeferredContext);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateBlendState1(const D3D11_BLEND_DESC1 *pBlendStateDesc, ID3D11BlendState1 **ppBlendState)
{
    if (_device1)
        _device1->CreateBlendState1(pBlendStateDesc, ppBlendState);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateRasterizerState1(const D3D11_RASTERIZER_DESC1 *pRasterizerDesc, ID3D11RasterizerState1 **ppRasterizerState)
{
    if (_device1)
        _device1->CreateRasterizerState1(pRasterizerDesc, ppRasterizerState);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL *pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL *pChosenFeatureLevel, ID3DDeviceContextState **ppContextState)
{
    if (_device1)
        _device1->CreateDeviceContextState(Flags, pFeatureLevels, FeatureLevels, SDKVersion, EmulatedInterface, pChosenFeatureLevel, ppContextState);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::OpenSharedResource1(HANDLE hResource, REFIID returnedInterface, void **ppResource)
{
    if (_device1)
        _device1->OpenSharedResource1(hResource, returnedInterface, ppResource);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID returnedInterface, void **ppResource)
{
    if (_device1)
        _device1->OpenSharedResourceByName(lpName, dwDesiredAccess, returnedInterface, ppResource);
    return E_NOTIMPL;
}

void D3D11DeviceProxy::GetImmediateContext2(ID3D11DeviceContext2 **ppImmediateContext)
{
    if (_device2)
        _device2->GetImmediateContext2(ppImmediateContext);
}

HRESULT D3D11DeviceProxy::CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2 **ppDeferredContext)
{
    if (_device2)
        _device2->CreateDeferredContext2(ContextFlags, ppDeferredContext);
    return E_NOTIMPL;
}

void D3D11DeviceProxy::GetResourceTiling(ID3D11Resource *pTiledResource, UINT *pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC *pPackedMipDesc, D3D11_TILE_SHAPE *pStandardTileShapeForNonPackedMips, UINT *pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING *pSubresourceTilingsForNonPackedMips)
{
    if (_device2)
        _device2->GetResourceTiling(pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, pStandardTileShapeForNonPackedMips, pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
}

HRESULT D3D11DeviceProxy::CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT *pNumQualityLevels)
{
    if (_device2)
        _device2->CheckMultisampleQualityLevels1(Format, SampleCount, Flags, pNumQualityLevels);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateTexture2D1(const D3D11_TEXTURE2D_DESC1 *pDesc1, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D1 **ppTexture2D)
{
    if (_device3)
        _device3->CreateTexture2D1(pDesc1, pInitialData, ppTexture2D);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateTexture3D1(const D3D11_TEXTURE3D_DESC1 *pDesc1, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture3D1 **ppTexture3D)
{
    if (_device3)
        _device3->CreateTexture3D1(pDesc1, pInitialData, ppTexture3D);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateRasterizerState2(const D3D11_RASTERIZER_DESC2 *pRasterizerDesc, ID3D11RasterizerState2 **ppRasterizerState)
{
    if (_device3)
        _device3->CreateRasterizerState2(pRasterizerDesc, ppRasterizerState);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateShaderResourceView1(ID3D11Resource *pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC1 *pDesc1, ID3D11ShaderResourceView1 **ppSRView1)
{
    if (_device3)
        _device3->CreateShaderResourceView1(pResource, pDesc1, ppSRView1);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateUnorderedAccessView1(ID3D11Resource *pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1 *pDesc1, ID3D11UnorderedAccessView1 **ppUAView1)
{
    if (_device3)
        _device3->CreateUnorderedAccessView1(pResource, pDesc1, ppUAView1);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateRenderTargetView1(ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC1 *pDesc1, ID3D11RenderTargetView1 **ppRTView1)
{
    if (_device3)
        _device3->CreateRenderTargetView1(pResource, pDesc1, ppRTView1);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateQuery1(const D3D11_QUERY_DESC1 *pQueryDesc1, ID3D11Query1 **ppQuery1)
{
    if (_device3)
        _device3->CreateQuery1(pQueryDesc1, ppQuery1);
    return E_NOTIMPL;
}

void D3D11DeviceProxy::GetImmediateContext3(ID3D11DeviceContext3 **ppImmediateContext)
{
    if (_device3)
        _device3->GetImmediateContext3(ppImmediateContext);
}

HRESULT D3D11DeviceProxy::CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3 **ppDeferredContext)
{
    if (_device3)
        _device3->CreateDeferredContext3(ContextFlags, ppDeferredContext);
    return E_NOTIMPL;
}

void D3D11DeviceProxy::WriteToSubresource(ID3D11Resource *pDstResource, UINT DstSubresource, const D3D11_BOX *pDstBox, const void *pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
    if (_device3)
        _device3->WriteToSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void D3D11DeviceProxy::ReadFromSubresource(void *pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource *pSrcResource, UINT SrcSubresource, const D3D11_BOX *pSrcBox)
{
    if (_device3)
        _device3->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, pSrcResource, SrcSubresource, pSrcBox);
}

HRESULT D3D11DeviceProxy::RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD *pdwCookie)
{
    if (_device4)
        _device4->RegisterDeviceRemovedEvent(hEvent, pdwCookie);
    return E_NOTIMPL;
}

void D3D11DeviceProxy::UnregisterDeviceRemoved(DWORD dwCookie)
{
    if (_device4)
        _device4->UnregisterDeviceRemoved(dwCookie);
}

HRESULT D3D11DeviceProxy::OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void **ppFence)
{
    if (_device5)
        _device5->OpenSharedFence(hFence, ReturnedInterface, ppFence);
    return E_NOTIMPL;
}

HRESULT D3D11DeviceProxy::CreateFence(UINT64 InitialValue, D3D11_FENCE_FLAG Flags, REFIID ReturnedInterface, void **ppFence)
{
    if (_device5)
        _device5->CreateFence(InitialValue, Flags, ReturnedInterface, ppFence);
    return E_NOTIMPL;
}

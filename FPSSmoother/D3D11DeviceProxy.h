#pragma once
#include <d3d11_4.h>
#include "Util.h"

class D3D11DeviceProxy : public ID3D11Device5
{
    ID3D11Device* _device = nullptr;
    ID3D11Device1* _device1 = nullptr;
    ID3D11Device2* _device2 = nullptr;
    ID3D11Device3* _device3 = nullptr;
    ID3D11Device4* _device4 = nullptr;
    ID3D11Device5* _device5 = nullptr;

public:
    D3D11DeviceProxy(ID3D11Device* device) : _device(device)
    {
    }
    D3D11DeviceProxy(ID3D11Device1* device) : _device(device), _device1(device)
    {
    }
    D3D11DeviceProxy(ID3D11Device2* device) : _device(device), _device1(device), _device2(device)
    {
    }
    D3D11DeviceProxy(ID3D11Device3* device) : _device(device), _device1(device), _device2(device), _device3(device)
    {
    }
    D3D11DeviceProxy(ID3D11Device4* device) : _device(device), _device1(device), _device2(device), _device3(device), _device4(device)
    {
    }
    D3D11DeviceProxy(ID3D11Device5* device) : _device(device), _device1(device), _device2(device), _device3(device), _device4(device), _device5(device)
    {
    }


    // Inherited via ID3D11Device5
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE CreateBuffer(const D3D11_BUFFER_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Buffer ** ppBuffer) override;
    virtual HRESULT STDMETHODCALLTYPE CreateTexture1D(const D3D11_TEXTURE1D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture1D ** ppTexture1D) override;
    virtual HRESULT STDMETHODCALLTYPE CreateTexture2D(const D3D11_TEXTURE2D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture2D ** ppTexture2D) override;
    virtual HRESULT STDMETHODCALLTYPE CreateTexture3D(const D3D11_TEXTURE3D_DESC * pDesc, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture3D ** ppTexture3D) override;
    virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView(ID3D11Resource * pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC * pDesc, ID3D11ShaderResourceView ** ppSRView) override;
    virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView(ID3D11Resource * pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC * pDesc, ID3D11UnorderedAccessView ** ppUAView) override;
    virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView(ID3D11Resource * pResource, const D3D11_RENDER_TARGET_VIEW_DESC * pDesc, ID3D11RenderTargetView ** ppRTView) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView(ID3D11Resource * pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC * pDesc, ID3D11DepthStencilView ** ppDepthStencilView) override;
    virtual HRESULT STDMETHODCALLTYPE CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC * pInputElementDescs, UINT NumElements, const void * pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout ** ppInputLayout) override;
    virtual HRESULT STDMETHODCALLTYPE CreateVertexShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11VertexShader ** ppVertexShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11GeometryShader ** ppGeometryShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(const void * pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY * pSODeclaration, UINT NumEntries, const UINT * pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage * pClassLinkage, ID3D11GeometryShader ** ppGeometryShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreatePixelShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11PixelShader ** ppPixelShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreateHullShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11HullShader ** ppHullShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDomainShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11DomainShader ** ppDomainShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreateComputeShader(const void * pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage * pClassLinkage, ID3D11ComputeShader ** ppComputeShader) override;
    virtual HRESULT STDMETHODCALLTYPE CreateClassLinkage(ID3D11ClassLinkage ** ppLinkage) override;
    virtual HRESULT STDMETHODCALLTYPE CreateBlendState(const D3D11_BLEND_DESC * pBlendStateDesc, ID3D11BlendState ** ppBlendState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC * pDepthStencilDesc, ID3D11DepthStencilState ** ppDepthStencilState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState(const D3D11_RASTERIZER_DESC * pRasterizerDesc, ID3D11RasterizerState ** ppRasterizerState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateSamplerState(const D3D11_SAMPLER_DESC * pSamplerDesc, ID3D11SamplerState ** ppSamplerState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateQuery(const D3D11_QUERY_DESC * pQueryDesc, ID3D11Query ** ppQuery) override;
    virtual HRESULT STDMETHODCALLTYPE CreatePredicate(const D3D11_QUERY_DESC * pPredicateDesc, ID3D11Predicate ** ppPredicate) override;
    virtual HRESULT STDMETHODCALLTYPE CreateCounter(const D3D11_COUNTER_DESC * pCounterDesc, ID3D11Counter ** ppCounter) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext ** ppDeferredContext) override;
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void ** ppResource) override;
    virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport(DXGI_FORMAT Format, UINT * pFormatSupport) override;
    virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT * pNumQualityLevels) override;
    virtual void STDMETHODCALLTYPE CheckCounterInfo(D3D11_COUNTER_INFO * pCounterInfo) override;
    virtual HRESULT STDMETHODCALLTYPE CheckCounter(const D3D11_COUNTER_DESC * pDesc, D3D11_COUNTER_TYPE * pType, UINT * pActiveCounters, LPSTR szName, UINT * pNameLength, LPSTR szUnits, UINT * pUnitsLength, LPSTR szDescription, UINT * pDescriptionLength) override;
    virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D11_FEATURE Feature, void * pFeatureSupportData, UINT FeatureSupportDataSize) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT * pDataSize, void * pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void * pData) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown * pData) override;
    virtual D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel(void) override;
    virtual UINT STDMETHODCALLTYPE GetCreationFlags(void) override;
    virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason(void) override;
    virtual void STDMETHODCALLTYPE GetImmediateContext(ID3D11DeviceContext ** ppImmediateContext) override;
    virtual HRESULT STDMETHODCALLTYPE SetExceptionMode(UINT RaiseFlags) override;
    virtual UINT STDMETHODCALLTYPE GetExceptionMode(void) override;
    virtual void STDMETHODCALLTYPE GetImmediateContext1(ID3D11DeviceContext1 ** ppImmediateContext) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1 ** ppDeferredContext) override;
    virtual HRESULT STDMETHODCALLTYPE CreateBlendState1(const D3D11_BLEND_DESC1 * pBlendStateDesc, ID3D11BlendState1 ** ppBlendState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState1(const D3D11_RASTERIZER_DESC1 * pRasterizerDesc, ID3D11RasterizerState1 ** ppRasterizerState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL * pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL * pChosenFeatureLevel, ID3DDeviceContextState ** ppContextState) override;
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResource1(HANDLE hResource, REFIID returnedInterface, void ** ppResource) override;
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID returnedInterface, void ** ppResource) override;
    virtual void STDMETHODCALLTYPE GetImmediateContext2(ID3D11DeviceContext2 ** ppImmediateContext) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2 ** ppDeferredContext) override;
    virtual void STDMETHODCALLTYPE GetResourceTiling(ID3D11Resource * pTiledResource, UINT * pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC * pPackedMipDesc, D3D11_TILE_SHAPE * pStandardTileShapeForNonPackedMips, UINT * pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING * pSubresourceTilingsForNonPackedMips) override;
    virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT * pNumQualityLevels) override;
    virtual HRESULT STDMETHODCALLTYPE CreateTexture2D1(const D3D11_TEXTURE2D_DESC1 * pDesc1, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture2D1 ** ppTexture2D) override;
    virtual HRESULT STDMETHODCALLTYPE CreateTexture3D1(const D3D11_TEXTURE3D_DESC1 * pDesc1, const D3D11_SUBRESOURCE_DATA * pInitialData, ID3D11Texture3D1 ** ppTexture3D) override;
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState2(const D3D11_RASTERIZER_DESC2 * pRasterizerDesc, ID3D11RasterizerState2 ** ppRasterizerState) override;
    virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView1(ID3D11Resource * pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC1 * pDesc1, ID3D11ShaderResourceView1 ** ppSRView1) override;
    virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView1(ID3D11Resource * pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1 * pDesc1, ID3D11UnorderedAccessView1 ** ppUAView1) override;
    virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView1(ID3D11Resource * pResource, const D3D11_RENDER_TARGET_VIEW_DESC1 * pDesc1, ID3D11RenderTargetView1 ** ppRTView1) override;
    virtual HRESULT STDMETHODCALLTYPE CreateQuery1(const D3D11_QUERY_DESC1 * pQueryDesc1, ID3D11Query1 ** ppQuery1) override;
    virtual void STDMETHODCALLTYPE GetImmediateContext3(ID3D11DeviceContext3 ** ppImmediateContext) override;
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3 ** ppDeferredContext) override;
    virtual void STDMETHODCALLTYPE WriteToSubresource(ID3D11Resource * pDstResource, UINT DstSubresource, const D3D11_BOX * pDstBox, const void * pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) override;
    virtual void STDMETHODCALLTYPE ReadFromSubresource(void * pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource * pSrcResource, UINT SrcSubresource, const D3D11_BOX * pSrcBox) override;
    virtual HRESULT STDMETHODCALLTYPE RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD * pdwCookie) override;
    virtual void STDMETHODCALLTYPE UnregisterDeviceRemoved(DWORD dwCookie) override;
    virtual HRESULT STDMETHODCALLTYPE OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void ** ppFence) override;
    virtual HRESULT STDMETHODCALLTYPE CreateFence(UINT64 InitialValue, D3D11_FENCE_FLAG Flags, REFIID ReturnedInterface, void ** ppFence) override;
};
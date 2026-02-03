#pragma once
#include <d3d12.h>
#include "ProxyBase.h"

class D3D12CommandQueueProxy : public ID3D12CommandQueue, public ProxyBase
{
    ID3D12CommandQueue *_queue = nullptr;

public:
    D3D12CommandQueueProxy(ID3D12CommandQueue *queue) : _queue(queue)
    {
    }

    virtual void CopyTo(ProxyBase *other) override {}

    // Inherited via ID3D12CommandQueue
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    virtual ULONG STDMETHODCALLTYPE AddRef(void) override;
    virtual ULONG STDMETHODCALLTYPE Release(void) override;
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT *data_size, void *data) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT data_size, const void *data) override;
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown *data) override;
    virtual HRESULT STDMETHODCALLTYPE SetName(const WCHAR *name) override;
    virtual HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void **ppvDevice) override;
    virtual void STDMETHODCALLTYPE UpdateTileMappings(ID3D12Resource *resource, UINT num_resource_regions, const D3D12_TILED_RESOURCE_COORDINATE *resource_region_start_coordinates, const D3D12_TILE_REGION_SIZE *resource_region_sizes, ID3D12Heap *heap, UINT num_ranges, const D3D12_TILE_RANGE_FLAGS *range_flags, const UINT *heap_range_start_offsets, const UINT *range_tile_counts, D3D12_TILE_MAPPING_FLAGS flags) override;
    virtual void STDMETHODCALLTYPE CopyTileMappings(ID3D12Resource *dst_resource, const D3D12_TILED_RESOURCE_COORDINATE *dst_region_start_coordinate, ID3D12Resource *src_resource, const D3D12_TILED_RESOURCE_COORDINATE *src_region_start_coordinate, const D3D12_TILE_REGION_SIZE *region_size, D3D12_TILE_MAPPING_FLAGS flags) override;
    virtual void STDMETHODCALLTYPE ExecuteCommandLists(UINT num_command_lists, ID3D12CommandList *const *command_lists) override;
    virtual void STDMETHODCALLTYPE SetMarker(UINT metadata, const void *data, UINT size) override;
    virtual void STDMETHODCALLTYPE BeginEvent(UINT metadata, const void *data, UINT size) override;
    virtual void STDMETHODCALLTYPE EndEvent(void) override;
    virtual HRESULT STDMETHODCALLTYPE Signal(ID3D12Fence *fence, UINT64 value) override;
    virtual HRESULT STDMETHODCALLTYPE Wait(ID3D12Fence *fence, UINT64 value) override;
    virtual HRESULT STDMETHODCALLTYPE GetTimestampFrequency(UINT64 *frequency) override;
    virtual HRESULT STDMETHODCALLTYPE GetClockCalibration(UINT64 *gpu_timestamp, UINT64 *cpu_timestamp) override;
    virtual D3D12_COMMAND_QUEUE_DESC *STDMETHODCALLTYPE GetDesc(D3D12_COMMAND_QUEUE_DESC *__ret) override;
};
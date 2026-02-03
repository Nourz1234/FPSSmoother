#include "D3D12CommandQueueProxy.h"
#include "../utils.h"
#include "../proxy_utils.h"

HRESULT D3D12CommandQueueProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"D3D12CommandQueueProxy::QueryInterface");

    if (IsEqualIID(riid, IID_GetSelf))
    {
        *ppvObject = this;
        return S_OK;
    }

    HRESULT hr = _queue->QueryInterface(riid, ppvObject);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppvObject, this);
    }

    return hr;
}

ULONG D3D12CommandQueueProxy::AddRef(void)
{
    inc_dbg_level(L"D3D12CommandQueueProxy::AddRef");
    return _queue->AddRef();
}

ULONG D3D12CommandQueueProxy::Release(void)
{
    inc_dbg_level(L"D3D12CommandQueueProxy::Release");
    return _queue->Release();
}

HRESULT D3D12CommandQueueProxy::GetPrivateData(REFGUID guid, UINT *data_size, void *data)
{
    return _queue->GetPrivateData(guid, data_size, data);
}

HRESULT D3D12CommandQueueProxy::SetPrivateData(REFGUID guid, UINT data_size, const void *data)
{
    return _queue->SetPrivateData(guid, data_size, data);
}

HRESULT D3D12CommandQueueProxy::SetPrivateDataInterface(REFGUID guid, const IUnknown *data)
{
    return _queue->SetPrivateDataInterface(guid, data);
}

HRESULT D3D12CommandQueueProxy::SetName(const WCHAR *name)
{
    return _queue->SetName(name);
}

HRESULT D3D12CommandQueueProxy::GetDevice(REFIID riid, void **ppvDevice)
{
    inc_dbg_level(L"D3D12CommandQueueProxy::GetDevice");

    HRESULT hr = _queue->GetDevice(riid, ppvDevice);
    if (SUCCEEDED(hr))
    {
        QueryProxy(riid, ppvDevice);
    }
    return hr;
}

void D3D12CommandQueueProxy::UpdateTileMappings(ID3D12Resource *resource, UINT num_resource_regions, const D3D12_TILED_RESOURCE_COORDINATE *resource_region_start_coordinates, const D3D12_TILE_REGION_SIZE *resource_region_sizes, ID3D12Heap *heap, UINT num_ranges, const D3D12_TILE_RANGE_FLAGS *range_flags, const UINT *heap_range_start_offsets, const UINT *range_tile_counts, D3D12_TILE_MAPPING_FLAGS flags)
{
    _queue->UpdateTileMappings(resource, num_resource_regions, resource_region_start_coordinates, resource_region_sizes, heap, num_ranges, range_flags, heap_range_start_offsets, range_tile_counts, flags);
}

void D3D12CommandQueueProxy::CopyTileMappings(ID3D12Resource *dst_resource, const D3D12_TILED_RESOURCE_COORDINATE *dst_region_start_coordinate, ID3D12Resource *src_resource, const D3D12_TILED_RESOURCE_COORDINATE *src_region_start_coordinate, const D3D12_TILE_REGION_SIZE *region_size, D3D12_TILE_MAPPING_FLAGS flags)
{
    _queue->CopyTileMappings(dst_resource, dst_region_start_coordinate, src_resource, src_region_start_coordinate, region_size, flags);
}

void D3D12CommandQueueProxy::ExecuteCommandLists(UINT num_command_lists, ID3D12CommandList *const *command_lists)
{
    _queue->ExecuteCommandLists(num_command_lists, command_lists);
}

void D3D12CommandQueueProxy::SetMarker(UINT metadata, const void *data, UINT size)
{
    _queue->SetMarker(metadata, data, size);
}

void D3D12CommandQueueProxy::BeginEvent(UINT metadata, const void *data, UINT size)
{
    _queue->BeginEvent(metadata, data, size);
}

void D3D12CommandQueueProxy::EndEvent(void)
{
    _queue->EndEvent();
}

HRESULT D3D12CommandQueueProxy::Signal(ID3D12Fence *fence, UINT64 value)
{
    return _queue->Signal(fence, value);
}

HRESULT D3D12CommandQueueProxy::Wait(ID3D12Fence *fence, UINT64 value)
{
    return _queue->Wait(fence, value);
}

HRESULT D3D12CommandQueueProxy::GetTimestampFrequency(UINT64 *frequency)
{
    return _queue->GetTimestampFrequency(frequency);
}

HRESULT D3D12CommandQueueProxy::GetClockCalibration(UINT64 *gpu_timestamp, UINT64 *cpu_timestamp)
{
    return _queue->GetClockCalibration(gpu_timestamp, cpu_timestamp);
}

D3D12_COMMAND_QUEUE_DESC *D3D12CommandQueueProxy::GetDesc(D3D12_COMMAND_QUEUE_DESC *__ret)
{
    return _queue->GetDesc(__ret);
}
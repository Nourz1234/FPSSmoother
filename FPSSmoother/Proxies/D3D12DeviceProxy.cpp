#include "D3D12DeviceProxy.h"
#include "../utils.h"
#include "../proxy_utils.h"

HRESULT D3D12DeviceProxy::QueryInterface(REFIID riid, void **ppvObject)
{
    inc_dbg_level(L"D3D12DeviceProxy::QueryInterface");

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

ULONG D3D12DeviceProxy::AddRef(void)
{
    return _device->AddRef();
}

ULONG D3D12DeviceProxy::Release(void)
{
    return _device->Release();
}

HRESULT D3D12DeviceProxy::GetPrivateData(REFGUID guid, UINT *data_size, void *data)
{
    return _device->GetPrivateData(guid, data_size, data);
}

HRESULT D3D12DeviceProxy::SetPrivateData(REFGUID guid, UINT data_size, const void *data)
{
    return _device->SetPrivateData(guid, data_size, data);
}

HRESULT D3D12DeviceProxy::SetPrivateDataInterface(REFGUID guid, const IUnknown *data)
{
    return _device->SetPrivateDataInterface(guid, data);
}

HRESULT D3D12DeviceProxy::SetName(const WCHAR *name)
{
    return _device->SetName(name);
}

UINT D3D12DeviceProxy::GetNodeCount()
{
    return _device->GetNodeCount();
}

HRESULT D3D12DeviceProxy::CreateCommandQueue(const D3D12_COMMAND_QUEUE_DESC *desc, REFIID riid, void **command_queue)
{
    inc_dbg_level(L"D3D12DeviceProxy::CreateCommandQueue");

    return _device->CreateCommandQueue(desc, riid, command_queue);
}

HRESULT D3D12DeviceProxy::CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE type, REFIID riid, void **command_allocator)
{
    return _device->CreateCommandAllocator(type, riid, command_allocator);
}

HRESULT D3D12DeviceProxy::CreateGraphicsPipelineState(const D3D12_GRAPHICS_PIPELINE_STATE_DESC *desc, REFIID riid, void **pipeline_state)
{
    return _device->CreateGraphicsPipelineState(desc, riid, pipeline_state);
}

HRESULT D3D12DeviceProxy::CreateComputePipelineState(const D3D12_COMPUTE_PIPELINE_STATE_DESC *desc, REFIID riid, void **pipeline_state)
{
    return _device->CreateComputePipelineState(desc, riid, pipeline_state);
}

HRESULT D3D12DeviceProxy::CreateCommandList(UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator *command_allocator, ID3D12PipelineState *initial_pipeline_state, REFIID riid, void **command_list)
{
    return _device->CreateCommandList(node_mask, type, command_allocator, initial_pipeline_state, riid, command_list);
}

HRESULT D3D12DeviceProxy::CheckFeatureSupport(D3D12_FEATURE feature, void *feature_data, UINT feature_data_size)
{
    return _device->CheckFeatureSupport(feature, feature_data, feature_data_size);
}

HRESULT D3D12DeviceProxy::CreateDescriptorHeap(const D3D12_DESCRIPTOR_HEAP_DESC *desc, REFIID riid, void **descriptor_heap)
{
    return _device->CreateDescriptorHeap(desc, riid, descriptor_heap);
}

UINT D3D12DeviceProxy::GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type)
{
    return _device->GetDescriptorHandleIncrementSize(descriptor_heap_type);
}

HRESULT D3D12DeviceProxy::CreateRootSignature(UINT node_mask, const void *bytecode, SIZE_T bytecode_length, REFIID riid, void **root_signature)
{
    return _device->CreateRootSignature(node_mask, bytecode, bytecode_length, riid, root_signature);
}

void D3D12DeviceProxy::CreateConstantBufferView(const D3D12_CONSTANT_BUFFER_VIEW_DESC *desc, D3D12_CPU_DESCRIPTOR_HANDLE descriptor)
{
    _device->CreateConstantBufferView(desc, descriptor);
}

void D3D12DeviceProxy::CreateShaderResourceView(ID3D12Resource *resource, const D3D12_SHADER_RESOURCE_VIEW_DESC *desc, D3D12_CPU_DESCRIPTOR_HANDLE descriptor)
{
    _device->CreateShaderResourceView(resource, desc, descriptor);
}

void D3D12DeviceProxy::CreateUnorderedAccessView(ID3D12Resource *resource, ID3D12Resource *counter_resource, const D3D12_UNORDERED_ACCESS_VIEW_DESC *desc, D3D12_CPU_DESCRIPTOR_HANDLE descriptor)
{
    _device->CreateUnorderedAccessView(resource, counter_resource, desc, descriptor);
}

void D3D12DeviceProxy::CreateRenderTargetView(ID3D12Resource *resource, const D3D12_RENDER_TARGET_VIEW_DESC *desc, D3D12_CPU_DESCRIPTOR_HANDLE descriptor)
{
    _device->CreateRenderTargetView(resource, desc, descriptor);
}

void D3D12DeviceProxy::CreateDepthStencilView(ID3D12Resource *resource, const D3D12_DEPTH_STENCIL_VIEW_DESC *desc, D3D12_CPU_DESCRIPTOR_HANDLE descriptor)
{
    _device->CreateDepthStencilView(resource, desc, descriptor);
}

void D3D12DeviceProxy::CreateSampler(const D3D12_SAMPLER_DESC *desc, D3D12_CPU_DESCRIPTOR_HANDLE descriptor)
{
    _device->CreateSampler(desc, descriptor);
}

void D3D12DeviceProxy::CopyDescriptors(UINT dst_descriptor_range_count, const D3D12_CPU_DESCRIPTOR_HANDLE *dst_descriptor_range_offsets, const UINT *dst_descriptor_range_sizes, UINT src_descriptor_range_count, const D3D12_CPU_DESCRIPTOR_HANDLE *src_descriptor_range_offsets, const UINT *src_descriptor_range_sizes, D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type)
{
    _device->CopyDescriptors(dst_descriptor_range_count, dst_descriptor_range_offsets, dst_descriptor_range_sizes, src_descriptor_range_count, src_descriptor_range_offsets, src_descriptor_range_sizes, descriptor_heap_type);
}

void D3D12DeviceProxy::CopyDescriptorsSimple(UINT descriptor_count, const D3D12_CPU_DESCRIPTOR_HANDLE dst_descriptor_range_offset, const D3D12_CPU_DESCRIPTOR_HANDLE src_descriptor_range_offset, D3D12_DESCRIPTOR_HEAP_TYPE descriptor_heap_type)
{
    _device->CopyDescriptorsSimple(descriptor_count, dst_descriptor_range_offset, src_descriptor_range_offset, descriptor_heap_type);
}

D3D12_RESOURCE_ALLOCATION_INFO *D3D12DeviceProxy::GetResourceAllocationInfo(D3D12_RESOURCE_ALLOCATION_INFO *__ret, UINT visible_mask, UINT resource_desc_count, const D3D12_RESOURCE_DESC *resource_descs)
{
    return _device->GetResourceAllocationInfo(__ret, visible_mask, resource_desc_count, resource_descs);
}

D3D12_HEAP_PROPERTIES *D3D12DeviceProxy::GetCustomHeapProperties(D3D12_HEAP_PROPERTIES *__ret, UINT node_mask, D3D12_HEAP_TYPE heap_type)
{
    return _device->GetCustomHeapProperties(__ret, node_mask, heap_type);
}

HRESULT D3D12DeviceProxy::CreateCommittedResource(const D3D12_HEAP_PROPERTIES *heap_properties, D3D12_HEAP_FLAGS heap_flags, const D3D12_RESOURCE_DESC *desc, D3D12_RESOURCE_STATES initial_state, const D3D12_CLEAR_VALUE *optimized_clear_value, REFIID riid, void **resource)
{
    return _device->CreateCommittedResource(heap_properties, heap_flags, desc, initial_state, optimized_clear_value, riid, resource);
}

HRESULT D3D12DeviceProxy::CreateHeap(const D3D12_HEAP_DESC *desc, REFIID riid, void **heap)
{
    return _device->CreateHeap(desc, riid, heap);
}

HRESULT D3D12DeviceProxy::CreatePlacedResource(ID3D12Heap *heap, UINT64 heap_offset, const D3D12_RESOURCE_DESC *desc, D3D12_RESOURCE_STATES initial_state, const D3D12_CLEAR_VALUE *optimized_clear_value, REFIID riid, void **resource)
{
    return _device->CreatePlacedResource(heap, heap_offset, desc, initial_state, optimized_clear_value, riid, resource);
}

HRESULT D3D12DeviceProxy::CreateReservedResource(const D3D12_RESOURCE_DESC *desc, D3D12_RESOURCE_STATES initial_state, const D3D12_CLEAR_VALUE *optimized_clear_value, REFIID riid, void **resource)
{
    return _device->CreateReservedResource(desc, initial_state, optimized_clear_value, riid, resource);
}

HRESULT D3D12DeviceProxy::CreateSharedHandle(ID3D12DeviceChild *object, const SECURITY_ATTRIBUTES *attributes, DWORD access, const WCHAR *name, HANDLE *handle)
{
    return _device->CreateSharedHandle(object, attributes, access, name, handle);
}

HRESULT D3D12DeviceProxy::OpenSharedHandle(HANDLE handle, REFIID riid, void **object)
{
    return _device->OpenSharedHandle(handle, riid, object);
}

HRESULT D3D12DeviceProxy::OpenSharedHandleByName(const WCHAR *name, DWORD access, HANDLE *handle)
{
    return _device->OpenSharedHandleByName(name, access, handle);
}

HRESULT D3D12DeviceProxy::MakeResident(UINT object_count, ID3D12Pageable *const *objects)
{
    return _device->MakeResident(object_count, objects);
}

HRESULT D3D12DeviceProxy::Evict(UINT object_count, ID3D12Pageable *const *objects)
{
    return _device->Evict(object_count, objects);
}

HRESULT D3D12DeviceProxy::CreateFence(UINT64 initial_value, D3D12_FENCE_FLAGS flags, REFIID riid, void **fence)
{
    return _device->CreateFence(initial_value, flags, riid, fence);
}

HRESULT D3D12DeviceProxy::GetDeviceRemovedReason()
{
    return _device->GetDeviceRemovedReason();
}

void D3D12DeviceProxy::GetCopyableFootprints(const D3D12_RESOURCE_DESC *desc, UINT first_sub_resource, UINT sub_resource_count, UINT64 base_offset, D3D12_PLACED_SUBRESOURCE_FOOTPRINT *layouts, UINT *row_count, UINT64 *row_size, UINT64 *total_bytes)
{
    _device->GetCopyableFootprints(desc, first_sub_resource, sub_resource_count, base_offset, layouts, row_count, row_size, total_bytes);
}

HRESULT D3D12DeviceProxy::CreateQueryHeap(const D3D12_QUERY_HEAP_DESC *desc, REFIID riid, void **heap)
{
    return _device->CreateQueryHeap(desc, riid, heap);
}

HRESULT D3D12DeviceProxy::SetStablePowerState(WINBOOL enable)
{
    return _device->SetStablePowerState(enable);
}

HRESULT D3D12DeviceProxy::CreateCommandSignature(const D3D12_COMMAND_SIGNATURE_DESC *desc, ID3D12RootSignature *root_signature, REFIID riid, void **command_signature)
{
    return _device->CreateCommandSignature(desc, root_signature, riid, command_signature);
}

void D3D12DeviceProxy::GetResourceTiling(ID3D12Resource *resource, UINT *total_tile_count, D3D12_PACKED_MIP_INFO *packed_mip_info, D3D12_TILE_SHAPE *standard_tile_shape, UINT *sub_resource_tiling_count, UINT first_sub_resource_tiling, D3D12_SUBRESOURCE_TILING *sub_resource_tilings)
{
    _device->GetResourceTiling(resource, total_tile_count, packed_mip_info, standard_tile_shape, sub_resource_tiling_count, first_sub_resource_tiling, sub_resource_tilings);
}

LUID *D3D12DeviceProxy::GetAdapterLuid(LUID *__ret)
{
    inc_dbg_level(L"D3D12DeviceProxy::GetAdapterLuid");

    return _device->GetAdapterLuid(__ret);
}

HRESULT D3D12DeviceProxy::CreatePipelineLibrary(const void *blob, SIZE_T blob_size, REFIID iid, void **lib)
{
    if (_device1)
        return _device1->CreatePipelineLibrary(blob, blob_size, iid, lib);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::SetEventOnMultipleFenceCompletion(ID3D12Fence *const *fences, const UINT64 *values, UINT fence_count, D3D12_MULTIPLE_FENCE_WAIT_FLAGS flags, HANDLE event)
{
    if (_device1)
        return _device1->SetEventOnMultipleFenceCompletion(fences, values, fence_count, flags, event);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::SetResidencyPriority(UINT object_count, ID3D12Pageable *const *objects, const D3D12_RESIDENCY_PRIORITY *priorities)
{
    if (_device1)
        return _device1->SetResidencyPriority(object_count, objects, priorities);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreatePipelineState(const D3D12_PIPELINE_STATE_STREAM_DESC *desc, REFIID riid, void **pipeline_state)
{
    if (_device2)
        return _device2->CreatePipelineState(desc, riid, pipeline_state);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::OpenExistingHeapFromAddress(const void *address, REFIID riid, void **heap)
{
    if (_device3)
        return _device3->OpenExistingHeapFromAddress(address, riid, heap);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::OpenExistingHeapFromFileMapping(HANDLE file_mapping, REFIID riid, void **heap)
{
    if (_device3)
        return _device3->OpenExistingHeapFromFileMapping(file_mapping, riid, heap);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::EnqueueMakeResident(D3D12_RESIDENCY_FLAGS flags, UINT num_objects, ID3D12Pageable *const *objects, ID3D12Fence *fence, UINT64 fence_value)
{
    if (_device3)
        return _device3->EnqueueMakeResident(flags, num_objects, objects, fence, fence_value);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateCommandList1(UINT node_mask, D3D12_COMMAND_LIST_TYPE type, D3D12_COMMAND_LIST_FLAGS flags, REFIID riid, void **command_list)
{
    if (_device4)
        return _device4->CreateCommandList1(node_mask, type, flags, riid, command_list);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateProtectedResourceSession(const D3D12_PROTECTED_RESOURCE_SESSION_DESC *desc, REFIID riid, void **session)
{
    if (_device4)
        return _device4->CreateProtectedResourceSession(desc, riid, session);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateCommittedResource1(const D3D12_HEAP_PROPERTIES *heap_properties, D3D12_HEAP_FLAGS heap_flags, const D3D12_RESOURCE_DESC *desc, D3D12_RESOURCE_STATES initial_resource_state, const D3D12_CLEAR_VALUE *optimized_clear_value, ID3D12ProtectedResourceSession *protected_session, REFIID riid_resource, void **resource)
{
    if (_device4)
        return _device4->CreateCommittedResource1(heap_properties, heap_flags, desc, initial_resource_state, optimized_clear_value, protected_session, riid_resource, resource);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateHeap1(const D3D12_HEAP_DESC *desc, ID3D12ProtectedResourceSession *protected_session, REFIID riid, void **heap)
{
    if (_device4)
        return _device4->CreateHeap1(desc, protected_session, riid, heap);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateReservedResource1(const D3D12_RESOURCE_DESC *desc, D3D12_RESOURCE_STATES initial_state, const D3D12_CLEAR_VALUE *optimized_clear_value, ID3D12ProtectedResourceSession *protected_session, REFIID riid, void **resource)
{
    if (_device4)
        return _device4->CreateReservedResource1(desc, initial_state, optimized_clear_value, protected_session, riid, resource);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

D3D12_RESOURCE_ALLOCATION_INFO *D3D12DeviceProxy::GetResourceAllocationInfo1(D3D12_RESOURCE_ALLOCATION_INFO *__ret, UINT visible_mask, UINT resource_descs_count, const D3D12_RESOURCE_DESC *resource_descs, D3D12_RESOURCE_ALLOCATION_INFO1 *resource_allocation_info1)
{
    if (_device4)
        return _device4->GetResourceAllocationInfo1(__ret, visible_mask, resource_descs_count, resource_descs, resource_allocation_info1);

    debug(L"Warning: Not implemented code path reached.");
    return nullptr;
}

HRESULT D3D12DeviceProxy::CreateLifetimeTracker(ID3D12LifetimeOwner *owner, REFIID riid, void **tracker)
{
    if (_device5)
        return _device5->CreateLifetimeTracker(owner, riid, tracker);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void D3D12DeviceProxy::RemoveDevice()
{
    if (_device5)
    {
        _device5->RemoveDevice();
        return;
    }

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT D3D12DeviceProxy::EnumerateMetaCommands(UINT *meta_commands_count, D3D12_META_COMMAND_DESC *descs)
{
    if (_device5)
        return _device5->EnumerateMetaCommands(meta_commands_count, descs);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::EnumerateMetaCommandParameters(REFGUID command_id, D3D12_META_COMMAND_PARAMETER_STAGE stage, UINT *total_structure_size_in_bytes, UINT *parameter_count, D3D12_META_COMMAND_PARAMETER_DESC *parameter_descs)
{
    if (_device5)
        return _device5->EnumerateMetaCommandParameters(command_id, stage, total_structure_size_in_bytes, parameter_count, parameter_descs);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateMetaCommand(REFGUID command_id, UINT node_mask, const void *creation_parameters_data, SIZE_T creation_parameters_data_size_in_bytes, REFIID riid, void **meta_command)
{
    if (_device5)
        return _device5->CreateMetaCommand(command_id, node_mask, creation_parameters_data, creation_parameters_data_size_in_bytes, riid, meta_command);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateStateObject(const D3D12_STATE_OBJECT_DESC *desc, REFIID riid, void **state_object)
{
    if (_device5)
        return _device5->CreateStateObject(desc, riid, state_object);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void D3D12DeviceProxy::GetRaytracingAccelerationStructurePrebuildInfo(const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS *desc, D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO *info)
{
    if (_device5)
    {
        _device5->GetRaytracingAccelerationStructurePrebuildInfo(desc, info);
        return;
    }

    debug(L"Warning: Not implemented code path reached.");
}

D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS D3D12DeviceProxy::CheckDriverMatchingIdentifier(D3D12_SERIALIZED_DATA_TYPE serialized_data_type, const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER *identifier_to_check)
{
    if (_device5)
        return _device5->CheckDriverMatchingIdentifier(serialized_data_type, identifier_to_check);

    debug(L"Warning: Not implemented code path reached.");
    return D3D12_DRIVER_MATCHING_IDENTIFIER_STATUS();
}

HRESULT D3D12DeviceProxy::SetBackgroundProcessingMode(D3D12_BACKGROUND_PROCESSING_MODE mode, D3D12_MEASUREMENTS_ACTION action, HANDLE event, WINBOOL *further_measurements_desired)
{
    inc_dbg_level(L"D3D12DeviceProxy::SetBackgroundProcessingMode");

    if (_device6)
        return _device6->SetBackgroundProcessingMode(mode, action, event, further_measurements_desired);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::AddToStateObject(const D3D12_STATE_OBJECT_DESC *addition, ID3D12StateObject *state_object_to_grow_from, REFIID riid, void **new_state_object)
{
    if (_device7)
        return _device7->AddToStateObject(addition, state_object_to_grow_from, riid, new_state_object);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateProtectedResourceSession1(const D3D12_PROTECTED_RESOURCE_SESSION_DESC1 *desc, REFIID riid, void **session)
{
    if (_device7)
        return _device7->CreateProtectedResourceSession1(desc, riid, session);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

D3D12_RESOURCE_ALLOCATION_INFO *D3D12DeviceProxy::GetResourceAllocationInfo2(D3D12_RESOURCE_ALLOCATION_INFO *__ret, UINT visible_mask, UINT resource_descs_count, const D3D12_RESOURCE_DESC1 *resource_descs, D3D12_RESOURCE_ALLOCATION_INFO1 *resource_allocation_info1)
{
    if (_device8)
        return _device8->GetResourceAllocationInfo2(__ret, visible_mask, resource_descs_count, resource_descs, resource_allocation_info1);

    debug(L"Warning: Not implemented code path reached.");
    return nullptr;
}

HRESULT D3D12DeviceProxy::CreateCommittedResource2(const D3D12_HEAP_PROPERTIES *heap_properties, D3D12_HEAP_FLAGS heap_flags, const D3D12_RESOURCE_DESC1 *desc, D3D12_RESOURCE_STATES initial_resource_state, const D3D12_CLEAR_VALUE *optimized_clear_value, ID3D12ProtectedResourceSession *protected_session, REFIID riid_resource, void **resource)
{
    if (_device8)
        return _device8->CreateCommittedResource2(heap_properties, heap_flags, desc, initial_resource_state, optimized_clear_value, protected_session, riid_resource, resource);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreatePlacedResource1(ID3D12Heap *heap, UINT64 heap_offset, const D3D12_RESOURCE_DESC1 *desc, D3D12_RESOURCE_STATES initial_state, const D3D12_CLEAR_VALUE *optimized_clear_value, REFIID riid, void **resource)
{
    if (_device8)
        return _device8->CreatePlacedResource1(heap, heap_offset, desc, initial_state, optimized_clear_value, riid, resource);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

void D3D12DeviceProxy::CreateSamplerFeedbackUnorderedAccessView(ID3D12Resource *targeted_resource, ID3D12Resource *feedback_resource, D3D12_CPU_DESCRIPTOR_HANDLE dst_descriptor)
{
    if (_device8)
    {
        _device8->CreateSamplerFeedbackUnorderedAccessView(targeted_resource, feedback_resource, dst_descriptor);
        return;
    }

    debug(L"Warning: Not implemented code path reached.");
}

void D3D12DeviceProxy::GetCopyableFootprints1(const D3D12_RESOURCE_DESC1 *resource_desc, UINT first_subresource, UINT subresources_count, UINT64 base_offset, D3D12_PLACED_SUBRESOURCE_FOOTPRINT *layouts, UINT *rows_count, UINT64 *row_size_in_bytes, UINT64 *total_bytes)
{
    if (_device8)
    {
        _device8->GetCopyableFootprints1(resource_desc, first_subresource, subresources_count, base_offset, layouts, rows_count, row_size_in_bytes, total_bytes);
        return;
    }

    debug(L"Warning: Not implemented code path reached.");
}

HRESULT D3D12DeviceProxy::CreateShaderCacheSession(const D3D12_SHADER_CACHE_SESSION_DESC *desc, REFIID riid, void **session)
{
    if (_device9)
        return _device9->CreateShaderCacheSession(desc, riid, session);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::ShaderCacheControl(D3D12_SHADER_CACHE_KIND_FLAGS kinds, D3D12_SHADER_CACHE_CONTROL_FLAGS control)
{
    if (_device9)
        return _device9->ShaderCacheControl(kinds, control);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

HRESULT D3D12DeviceProxy::CreateCommandQueue1(const D3D12_COMMAND_QUEUE_DESC *desc, REFIID creator_id, REFIID riid, void **command_queue)
{
    inc_dbg_level(L"D3D12DeviceProxy::CreateCommandQueue1");

    if (_device9)
        return _device9->CreateCommandQueue1(desc, creator_id, riid, command_queue);

    debug(L"Warning: Not implemented code path reached.");
    return E_NOTIMPL;
}

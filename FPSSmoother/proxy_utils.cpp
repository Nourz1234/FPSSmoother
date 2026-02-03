#include "Proxies/DXGIDeviceProxy.h"
#include "Proxies/D3D11DeviceProxy.h"
#include "Proxies/D3D12DeviceProxy.h"
#include "Proxies/DXGIObjectProxy.h"
#include "Proxies/DXGIAdapterProxy.h"
#include "Proxies/DXGIFactoryProxy.h"
#include "Proxies/DXGIOutputProxy.h"
#include "Proxies/DXGISwapChainProxy.h"
#include "Proxies/D3D12CommandQueueProxy.h"
#include "utils.h"
#include "proxy_utils.h"

bool QueryProxy(REFIID riid, void **ppvObject)
{
    ProxyHelper proxyHelper;
    // ID3D11Device
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device4>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D11DeviceProxy, ID3D11Device5>(riid, ppvObject);
    // ID3D12Device
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device4>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device5>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device6>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device7>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device8>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12DeviceProxy, ID3D12Device9>(riid, ppvObject);
    // ID3D12CommandQueue
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<D3D12CommandQueueProxy, ID3D12CommandQueue>(riid, ppvObject);
    // IDXGIDevice
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIDeviceProxy, IDXGIDevice4>(riid, ppvObject);
    // IDXGIAdapter
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIAdapterProxy, IDXGIAdapter4>(riid, ppvObject);
    // IDXGIFactory
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory4>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory5>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory6>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIFactoryProxy, IDXGIFactory7>(riid, ppvObject);
    // IDXGIOutput
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput4>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput5>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIOutputProxy, IDXGIOutput6>(riid, ppvObject);
    // IDXGISwapChain
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain1>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain2>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain3>(riid, ppvObject);
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGISwapChainProxy, IDXGISwapChain4>(riid, ppvObject);
    // IDXGIObject
    proxyHelper.TryGetProxyForThisInterfaceForMePwease<DXGIObjectProxy, IDXGIObject>(riid, ppvObject);

    proxyHelper.AndThankYou(riid, ppvObject);
    return proxyHelper.UwU();
}

void QueryProxy(REFIID riid, void **ppvObject, ProxyBase *proxy)
{
    if (QueryProxy(riid, ppvObject))
        proxy->CopyTo((ProxyBase *)*ppvObject);
}

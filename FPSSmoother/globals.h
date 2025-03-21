#pragma once
#include <d3d11.h>
#include <initguid.h>
#include <guiddef.h>

#define DEBUG_BUILD

DEFINE_GUID(IID_GetSelf, 0x0fffffff, 0xffff, 0xffff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);


extern bool g_SetSwapEffect;
extern DXGI_SWAP_EFFECT g_SwapEffect;
extern bool g_SetSwapChainBufferCount;
extern int g_SwapChainBufferCount;
extern bool g_SetPreferredRefreshRate;
extern int g_PreferredRefreshRate;
extern bool g_SetSyncInterval;
extern int g_SyncInterval;
extern bool g_SetMaximumFrameLatency;
extern int g_MaximumFrameLatency;
extern bool g_SetAllowTearing;
extern bool g_AllowTearing;
extern bool g_SetFPSLimit;
extern int g_FPSLimit;

extern bool g_DXGIHooking;
extern bool g_D3D11Hooking;

extern int g_StahpBruh;
extern int g_DbgLevel;
extern int g_NumProxies;


class DbgLevel
{
public:
    DbgLevel()
    {
        g_DbgLevel += 1;
    }
    ~DbgLevel()
    {
        g_DbgLevel -= 1;
    }
};


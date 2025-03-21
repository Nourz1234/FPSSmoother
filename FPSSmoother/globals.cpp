#include "globals.h"


bool g_SetSwapEffect = false;
DXGI_SWAP_EFFECT g_SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
bool g_SetSwapChainBufferCount = false;
int g_SwapChainBufferCount = 2;
bool g_SetPreferredRefreshRate = false;
int g_PreferredRefreshRate = 60;
bool g_SetSyncInterval = false;
int g_SyncInterval = 0;
bool g_SetMaximumFrameLatency = false;
int g_MaximumFrameLatency = 3;
bool g_SetAllowTearing = false;
bool g_AllowTearing = true;
bool g_SetFPSLimit = false;
int g_FPSLimit = 60;

bool g_DXGIHooking = true;
bool g_D3D11Hooking = false;

int g_StahpBruh = 0;
int g_DbgLevel = 0;
int g_NumProxies = 0;


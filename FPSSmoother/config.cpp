#include <pathcch.h>
#include <stdexcept>

#include "utils.h"
#include "globals.h"
#include "config.h"

void LoadConfig()
{
    WCHAR iniPath[512];
    GetModuleFileName(NULL, iniPath, ARRAYSIZE(iniPath));
    PathCchRemoveFileSpec(iniPath, ARRAYSIZE(iniPath));
    PathCchAppend(iniPath, ARRAYSIZE(iniPath), L"fpss.ini");

#define ReadIniValue(ValueName)  \
    std::wstring s##ValueName;   \
    do                           \
    {                            \
        WCHAR buff[512]{};       \
        GetPrivateProfileString( \
            L"Preferences",      \
            L## #ValueName,      \
            NULL,                \
            buff,                \
            ARRAYSIZE(buff),     \
            iniPath);            \
        s##ValueName = buff;     \
    } while (false)

    ReadIniValue(FullscreenMode);
    ReadIniValue(VSyncMode);
    ReadIniValue(PreferredRefreshRate);
    ReadIniValue(SwapChainBufferCount);
    ReadIniValue(SwapEffect);
    ReadIniValue(MaximumFrameLatency);
    ReadIniValue(AllowTearing);
    ReadIniValue(FPSLimit);

    if (lstrcmpi(sFullscreenMode.c_str(), L"On") == 0)
    {
        g_SetFullscreenMode = true;
        g_FullscreenMode = true;
        debug(L"FullscreenMode: On");
    }
    else if (lstrcmpi(sFullscreenMode.c_str(), L"Off") == 0)
    {
        g_SetFullscreenMode = true;
        g_FullscreenMode = false;
        debug(L"FullscreenMode: Off");
    }
    else
    {
        g_SetFullscreenMode = false;
        debug(L"FullscreenMode: Default");
    }

    if (lstrcmpi(sVSyncMode.c_str(), L"Off") == 0)
    {
        g_SetSyncInterval = true;
        g_SyncInterval = 0;
        debug(L"VSyncMode: Off");
    }
    else if (lstrcmpi(sVSyncMode.c_str(), L"On") == 0)
    {
        g_SetSyncInterval = true;
        g_SyncInterval = 1;
        debug(L"VSyncMode: On");
    }
    else if (lstrcmpi(sVSyncMode.c_str(), L"OnHalfRefreshRate") == 0)
    {
        g_SetSyncInterval = true;
        g_SyncInterval = 2;
        debug(L"VSyncMode: OnHalfRefreshRate");
    }
    else
    {
        g_SetSyncInterval = false;
        debug(L"VSyncMode: Default");
    }

    if (lstrcmpi(sPreferredRefreshRate.c_str(), L"Default") == 0)
    {
        g_SetPreferredRefreshRate = false;
        debug(L"PreferredRefreshRate: Default");
    }
    else
    {
        try
        {
            g_PreferredRefreshRate = std::stoi(sPreferredRefreshRate);
            g_SetPreferredRefreshRate = true;
            debug(L"PreferredRefreshRate: %d", g_PreferredRefreshRate);
        }
        catch (std::invalid_argument)
        {
            g_SetPreferredRefreshRate = false;
            debug(L"PreferredRefreshRate: Default");
        }
    }

    if (lstrcmpi(sSwapChainBufferCount.c_str(), L"Default") == 0)
    {
        g_SetSwapChainBufferCount = false;
        debug(L"SwapChainBufferCount: Default");
    }
    else
    {
        try
        {
            g_SwapChainBufferCount = std::stoi(sSwapChainBufferCount);
            g_SetSwapChainBufferCount = true;
            debug(L"SwapChainBufferCount: %d", g_SwapChainBufferCount);
        }
        catch (std::invalid_argument)
        {
            g_SetSwapChainBufferCount = false;
            debug(L"SwapChainBufferCount: Default");
        }
    }

    if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_DISCARD") == 0)
    {
        g_SetSwapEffect = true;
        g_SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        debug(L"SwapEffect: DXGI_SWAP_EFFECT_DISCARD");
    }
    else if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_SEQUENTIAL") == 0)
    {
        g_SetSwapEffect = true;
        g_SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
        debug(L"SwapEffect: DXGI_SWAP_EFFECT_SEQUENTIAL");
    }
    else if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_FLIP_DISCARD") == 0)
    {
        g_SetSwapEffect = true;
        g_SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        debug(L"SwapEffect: DXGI_SWAP_EFFECT_FLIP_DISCARD");
    }
    else if (lstrcmpi(sSwapEffect.c_str(), L"DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL") == 0)
    {
        g_SetSwapEffect = true;
        g_SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        debug(L"SwapEffect: DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL");
    }
    else
    {
        g_SetSwapEffect = false;
        debug(L"SwapEffect: Default");
    }

    if (lstrcmpi(sMaximumFrameLatency.c_str(), L"Default") == 0)
    {
        g_SetMaximumFrameLatency = false;
        debug(L"MaximumFrameLatency: Default");
    }
    else
    {
        try
        {
            g_MaximumFrameLatency = std::stoi(sMaximumFrameLatency);
            g_SetMaximumFrameLatency = true;
            debug(L"MaximumFrameLatency: %d", g_MaximumFrameLatency);
        }
        catch (std::invalid_argument)
        {
            g_SetMaximumFrameLatency = false;
            debug(L"MaximumFrameLatency: Default");
        }
    }

    if (lstrcmpi(sAllowTearing.c_str(), L"On") == 0)
    {
        g_SetAllowTearing = true;
        g_AllowTearing = true;
        debug(L"AllowTearing: On");
    }
    else if (lstrcmpi(sAllowTearing.c_str(), L"Off") == 0)
    {
        g_SetAllowTearing = true;
        g_AllowTearing = false;
        debug(L"AllowTearing: Off");
    }
    else
    {
        g_SetAllowTearing = false;
        debug(L"AllowTearing: Default");
    }

    if (lstrcmpi(sFPSLimit.c_str(), L"Off") == 0)
    {
        g_SetFPSLimit = false;
        debug(L"FPSLimit: Off");
    }
    else
    {
        try
        {
            g_FPSLimit = std::stoi(sFPSLimit);
            g_SetFPSLimit = true;
            debug(L"FPSLimit: %d", g_FPSLimit);
        }
        catch (std::invalid_argument)
        {
            g_SetFPSLimit = false;
            debug(L"FPSLimit: Off");
        }
    }
}

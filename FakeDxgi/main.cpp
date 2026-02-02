#include <Windows.h>
#include <stdio.h>
#include <pathcch.h>

#include "FPSSmoother/globals.h"
#include "FPSSmoother/config.h"
#include "dxgi.h"
#include "d3d11.h"
#include "d3d12.h"

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpvReserved)
{

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
    {
#ifdef DEBUG
        AllocConsole();
        FILE *oldStream = NULL;
        freopen_s(&oldStream, "CONOUT$", "w", stdout);
#endif

        LoadConfig();
        DXGIMain();
        PatchD3D11();
        PatchD3D12();
        break;
    }

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

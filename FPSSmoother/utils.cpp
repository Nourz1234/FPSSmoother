#include "utils.h"
#include <pathcch.h>

#ifdef DEBUG

LPCSTR GetMB(LPCWSTR wc)
{
    static char c[1024];
    size_t numCharsConverted;
    wcstombs_s(&numCharsConverted, c, wc, 1024);
    return c;
}

LPCWSTR GetWC(LPCSTR c)
{
    static wchar_t wc[1024];
    size_t numCharsConverted;
    mbstowcs_s(&numCharsConverted, wc, c, 1024);
    return wc;
}

LPCWSTR SwapChainSwapEffectToStr(DXGI_SWAP_EFFECT SwapEffect)
{
    static wchar_t lpStr[1024]{};

    if (SwapEffect == DXGI_SWAP_EFFECT_DISCARD)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_DISCARD");
    if (SwapEffect == DXGI_SWAP_EFFECT_SEQUENTIAL)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_SEQUENTIAL");
    if (SwapEffect == DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL");
    if (SwapEffect == DXGI_SWAP_EFFECT_FLIP_DISCARD)
        swprintf_s(lpStr, L"DXGI_SWAP_EFFECT_FLIP_DISCARD");

    return lpStr;
}

LPCWSTR SwapChainFlagsToStr(UINT Flags)
{
    std::wstring str = L"";

    if (Flags & DXGI_SWAP_CHAIN_FLAG_NONPREROTATED)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_NONPREROTATED ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_NONPREROTATED)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_NONPREROTATED ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING ");
    if (Flags & DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS)
        str.append(L"DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS ");

    static wchar_t lpStr[1024]{};
    swprintf_s(lpStr, str.c_str());
    return lpStr;
}

void fdebug(std::wstring str)
{
    static FILE *logFile = nullptr;
    if (!logFile)
    {
        WCHAR logPath[MAX_PATH] = L"";
        GetModuleFileName(NULL, logPath, ARRAYSIZE(logPath));
        PathCchRemoveFileSpec(logPath, ARRAYSIZE(logPath));
        PathCchAppend(logPath, ARRAYSIZE(logPath), L"dxgi.log");

        fopen_s(&logFile, GetMB(logPath), "w");
    }
    if (logFile)
    {
        fwprintf_s(logFile, str.c_str());
        fflush(logFile);
    }
}

void debug(const wchar_t *_Format, ...)
{
    WCHAR buff[1024];

    va_list args;
    va_start(args, _Format);
    vswprintf_s(buff, 1024, _Format, args);
    va_end(args);

    std::wstring str = L"";
    for (int i = 0; i < g_DbgLevel; ++i)
    {
        str.append(L"  ");
    }
    str.append(buff);
    str.append(L"\n");
    wprintf_s(str.c_str());

    fdebug(str);
}

#endif // DEBUG

FARPROC GetProcAddress2(LPCSTR dllName, LPCSTR funcName)
{
    HMODULE hMod = GetModuleHandleA(dllName);
    if (!hMod)
    {
        hMod = LoadLibraryA(dllName);
    }
    return GetProcAddress(hMod, funcName);
}
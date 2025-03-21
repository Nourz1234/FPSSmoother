#include "Util.h"
#include <pathcch.h>

#pragma comment(lib, "Pathcch.lib")


#ifdef DEBUG_BUILD

const char* GetMB(const wchar_t *wc)
{
    static char c[1024];
    size_t numCharsConverted;
    wcstombs_s(&numCharsConverted, c, wc, 1024);
    return c;
}

const wchar_t* GetWC(const char *c)
{
    static wchar_t wc[1024];
    size_t numCharsConverted;
    mbstowcs_s(&numCharsConverted, wc, c, 1024);
    return wc;
}

void fdebug(std::wstring str)
{
    static FILE* logFile = nullptr;
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

#endif // DEBUG_BUILD



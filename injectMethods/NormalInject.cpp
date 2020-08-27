#include <windows.h>
#include <tlhelp32.h>

bool NormalInject(HANDLE hProcess, const char* dllpath)
{
    int nSize = strlen(dllpath) + 1;
    if (!hProcess) return false;


    LPVOID pDLLPathAddr = VirtualAllocEx(hProcess, 0, nSize,
                                         MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if(!pDLLPathAddr)
    {
        return false;
    }

    if(!WriteProcessMemory(hProcess, pDLLPathAddr, dllpath, nSize, 0))
    {
        return false;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, 0, 0,
                                        (LPTHREAD_START_ROUTINE)LoadLibraryA, pDLLPathAddr,
                                        0, 0);
    if(!hThread)
    {
        return false;
    }
    WaitForSingleObject(hThread, INFINITE);

    VirtualFreeEx(hProcess, pDLLPathAddr, 0, MEM_RELEASE);
    CloseHandle(hThread);
    return  true;
}

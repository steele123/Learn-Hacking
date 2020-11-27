// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

void CheckForKeys()
{
    if (GetAsyncKeyState(VK_NUMPAD1) & 1) 
    {
    }
}

DWORD WINAPI MainThread(HMODULE hModule) 
{
#if DEBUG
    AllocConsole();
    FILE* f = nullptr;
    freopen_s(&f, "CONOUT$", "w", stdout);
#endif

    while (true) 
    {
        Sleep(20);
        CheckForKeys();
        if (GetAsyncKeyState(VK_END) & 1) 
        {
            // Exit while loop
            break;
        }
    }

    // Clean up our injection
    Sleep(100);
#if DEBUG
    if (f) fclose(f);
    FreeConsole();
#endif
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


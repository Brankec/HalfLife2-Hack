#include "WndHook.h"

//all game hacking logic is done inside mainhack.cpp
DWORD WINAPI MainThread(PVOID base)
{
    WndHook::Hook(base);

    //FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    //FreeLibraryAndExitThread((base), 1);
    FreeLibrary((HMODULE)base);
    ExitThread(0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


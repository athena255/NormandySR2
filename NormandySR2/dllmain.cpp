// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "globals.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        LdrDisableThreadCalloutsForDll(hModule);
        g::gameMan = new GameManager();
        g::cheatMan = new CheatManager();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        // Restore the VT table
        g::gameMan->~GameManager();
        break;
    }
    return TRUE;
}


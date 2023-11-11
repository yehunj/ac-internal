#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>
#include <thread>

#undef WIN32_LEAN_AND_MEAN


DWORD __stdcall Thread(LPVOID reserved)
{
    uintptr_t execBase = (uintptr_t)(GetModuleHandleA(nullptr)); 

    uintptr_t* localPlayerPtr = (uintptr_t*)(execBase + 0x0017E0A8);

    int ammoOffset = 0x140;
    int healthOffset = 0xEC;

    uintptr_t ammoAddr = *localPlayerPtr + ammoOffset;
    uintptr_t healthAddr = *localPlayerPtr + healthOffset;

    while (localPlayerPtr) 
    {   
        
        // z
        if (GetAsyncKeyState(0x5A)) {
            *(int*)healthAddr = 1000;
        }
        // x 
        if (GetAsyncKeyState(0x58)) {
            *(int*)ammoAddr = 1000;
        }

        Sleep(100);
    }

    FreeLibraryAndExitThread((HMODULE) reserved, 0);

}

BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(instance);

        CreateThread(
            nullptr,
            0,
            Thread,
            instance,
            0,
            nullptr
        );
        break;
    }

    return TRUE; 

}



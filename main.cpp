#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>
//#include <iostream>

#include "Global.h"
#include "START_POINT.h"
#include "Aimbot.h"
#include "Offsets/Client.h"
#include "Offsets/Offset.h"

//Creating Console
/*void CreateConsole()
{
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
}*/

//StartPoint
void StartPoint(HINSTANCE Instance)
{
    //CreateConsole();
    uintptr_t CLIENT = (uintptr_t)GetModuleHandle("client.dll");
    std::vector<uintptr_t> ENEMY_PTRS;

    while (!GetAsyncKeyState(VK_END))
    {
        Entity_Finder(ENEMY_PTRS, CLIENT);
        std::vector<uintptr_t> ENEMY_LIST;
        GET_ENTITY_LIST(ENEMY_LIST);

        /*system("cls");
        for (auto x : ENEMY_LIST)
        {
            std::cout << x << std::endl;
        }*/

        std::this_thread::sleep_for(std::chrono::milliseconds(5)); //Performance
    }

    //FreeConsole();
    FreeLibraryAndExitThread(Instance, 0);
    return;
}

void Aimbot(HINSTANCE Instance)
{
    uintptr_t CLIENT = (uintptr_t)GetModuleHandle("client.dll");
    
    while (!GetAsyncKeyState(VK_END))
    {
        EXECUTE(CLIENT);
    }
    
    FreeLibraryAndExitThread(Instance, 0);
    return;
}

//DLL entry point
BOOL WINAPI DllMain(
    HINSTANCE Instance,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    //on attach
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(Instance);

        //Starting Cheat
        auto HackThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartPoint), Instance, 0, nullptr);
        auto AimbotThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Aimbot), Instance, 0, nullptr);

        //Ending cheat
        if (HackThread) CloseHandle(HackThread);
        if (AimbotThread) CloseHandle(AimbotThread);
    }

    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
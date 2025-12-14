/*
This file was created by
12345koip for the LuGo executor
on 13/12/2025. See LICENSE and README
for details.
*/

#include <thread>
#include "Logger/Logger.hpp"


static void Entry() {
    LuGo::IO::Logger::GetSingleton();
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved) {
    switch (dwReasonForCall) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(hModule);
            std::thread(Entry).detach();
            break;
        }
    }

    return TRUE;
}
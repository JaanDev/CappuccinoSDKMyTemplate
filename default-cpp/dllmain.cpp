#include "pch.h"


DWORD WINAPI my_thread(void* hModule) {
#ifdef DEBUG
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif // DEBUG

    // Hook Proccess if the minhook library was not found (Important if you are using minhook
	
	if(MH_Initialize() != MH_OK){
		
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
		
	}
	
	//

    MH_EnableHook(MH_ALL_HOOKS);

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


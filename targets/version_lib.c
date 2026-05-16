#include <windows.h>
#include "dll_wrapper.h"
#include "wnd_search.h"

WINAPI BOOL DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstDLL);
            dll_wrap_init();
            wnd_search_init();
            break;

        case DLL_PROCESS_DETACH:
            dll_wrap_free();
            wnd_search_free();
            break;

        default: break;
    }
    return TRUE;
}

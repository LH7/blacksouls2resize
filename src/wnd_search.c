#include "wnd_search.h"

#define INTERVAL_WINDOW_SEARCH_MS 100
#define INTERVAL_CHECK_WND_PROC_MS 500

typedef struct {
    DWORD processId;
    HWND hwnd;
} FindWindowData_t;

static BOOL bKeepSearch = TRUE;
static HANDLE hSearchThread = NULL;
static HWND hTargetWnd = NULL;

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    FindWindowData_t* data = (FindWindowData_t*)lParam;

    DWORD processId = 0;
    GetWindowThreadProcessId(hwnd, &processId);

    if (processId == data->processId && GetWindow(hwnd, GW_OWNER) == NULL && IsWindowVisible(hwnd)) {
        data->hwnd = hwnd;
        return FALSE;
    }
    return TRUE;
}

static DWORD WINAPI SearchWindowThread(LPVOID lpParam) {
    FindWindowData_t data = {GetCurrentProcessId(), NULL };

    while (data.hwnd == NULL) {
        Sleep(INTERVAL_WINDOW_SEARCH_MS);
        EnumWindows(&EnumWindowsProc, (LPARAM)&data);
    }
    hTargetWnd = data.hwnd;

    wnd_styles_set(hTargetWnd);
    wnd_proc_set(hTargetWnd);

    while (bKeepSearch && IsWindow(hTargetWnd)) {
        Sleep(INTERVAL_CHECK_WND_PROC_MS);
        wnd_proc_restore_if_replaced(hTargetWnd);
    }
    return 0;
}

void wnd_search_init() {
    bKeepSearch = TRUE;
    hSearchThread = CreateThread(NULL, 0, SearchWindowThread, NULL, 0, NULL);
}

void wnd_search_free() {
    wnd_proc_restore(hTargetWnd);
    bKeepSearch = FALSE;
    if (hSearchThread) {
        CloseHandle(hSearchThread);
        hSearchThread = NULL;
    }
}

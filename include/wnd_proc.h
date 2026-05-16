#ifndef _WND_PROC_H
#define _WND_PROC_H
#include <windows.h>

    void wnd_proc_set(HWND hTargetWnd);
    void wnd_proc_restore(HWND hTargetWnd);
    void wnd_proc_restore_if_replaced(HWND hTargetWnd);

#endif

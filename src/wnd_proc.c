#include "wnd_proc.h"

#define TARGET_ASPECT (4.0 / 3.0)

static WNDPROC pOriginalWndProc = NULL;
static LONG_PTR pWndProcAddress = 0;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LPRECT rect;

    switch (uMsg) {
        case WM_SIZING:
            rect = (LPRECT)lParam;
            LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
            LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
            BOOL hasMenu = (GetMenu(hwnd) != NULL);

            RECT borderRect = {0, 0, 0, 0};
            AdjustWindowRectEx(&borderRect, style, hasMenu, exStyle);

            int borderWidth = (borderRect.right - borderRect.left);
            int borderHeight = (borderRect.bottom - borderRect.top);

            int currentClientWidth = (rect->right - rect->left) - borderWidth;
            int currentClientHeight = (rect->bottom - rect->top) - borderHeight;

            switch (wParam) {
                case WMSZ_TOP:
                case WMSZ_BOTTOM:
                    // ширина в зависимости от высоты
                    currentClientWidth = (int)(currentClientHeight * TARGET_ASPECT);
                    break;

                default:
                    // приоритет на ширину, даже если изменения за угол
                    currentClientHeight = (int)(currentClientWidth / TARGET_ASPECT);
                    break;
            }

            RECT finalClientRect = {0, 0, currentClientWidth, currentClientHeight};
            AdjustWindowRectEx(&finalClientRect, style, hasMenu, exStyle);

            int finalWindowWidth = finalClientRect.right - finalClientRect.left;
            int finalWindowHeight = finalClientRect.bottom - finalClientRect.top;

            switch (wParam) {
                case WMSZ_LEFT:
                case WMSZ_TOPLEFT:
                case WMSZ_BOTTOMLEFT:
                    rect->left = rect->right - finalWindowWidth;
                    break;
                default:
                    rect->right = rect->left + finalWindowWidth;
                    break;
            }
            switch (wParam) {
                case WMSZ_TOP:
                case WMSZ_TOPLEFT:
                case WMSZ_TOPRIGHT:
                    rect->top = rect->bottom - finalWindowHeight;
                    break;
                default:
                    rect->bottom = rect->top + finalWindowHeight;
                    break;
            }

            return TRUE;

        case WM_DESTROY:
            wnd_proc_restore(hwnd);
            break;

        default:
            break;
    }

    return CallWindowProc(pOriginalWndProc, hwnd, uMsg, wParam, lParam);
}

void wnd_proc_set(HWND hTargetWnd) {
    pWndProcAddress = (LONG_PTR)WndProc;
    pOriginalWndProc = (WNDPROC)SetWindowLongPtr(hTargetWnd, GWLP_WNDPROC, pWndProcAddress);
}

void wnd_proc_restore_if_replaced(HWND hTargetWnd) {
    LONG_PTR currentWndProc = GetWindowLongPtr(hTargetWnd, GWLP_WNDPROC);
    if (currentWndProc != 0 && currentWndProc != pWndProcAddress) {
        pOriginalWndProc = (WNDPROC)currentWndProc;
        SetWindowLongPtr(hTargetWnd, GWLP_WNDPROC, pWndProcAddress);
    }
}

void wnd_proc_restore(HWND hTargetWnd) {
    if (hTargetWnd && IsWindow(hTargetWnd) && pWndProcAddress) {
        LONG_PTR currentWndProc = GetWindowLongPtr(hTargetWnd, GWLP_WNDPROC);
        if (currentWndProc == pWndProcAddress) {
            SetWindowLongPtr(hTargetWnd, GWLP_WNDPROC, (LONG_PTR)pOriginalWndProc);
        }
    }
}
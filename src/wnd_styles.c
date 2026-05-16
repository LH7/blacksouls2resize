#include "wnd_styles.h"

void wnd_styles_set(HWND hTargetWnd) {
    LONG_PTR style = GetWindowLongPtr(hTargetWnd, GWL_STYLE);
    style |= (WS_THICKFRAME | WS_MAXIMIZEBOX); // NOLINT(hicpp-signed-bitwise)
    SetWindowLongPtr(hTargetWnd, GWL_STYLE, style);
    SetWindowPos(hTargetWnd, NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED // NOLINT(hicpp-signed-bitwise)
    );
}
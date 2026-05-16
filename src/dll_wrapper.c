#include "dll_wrapper.h"

static HINSTANCE hInstOrigDll = 0;
static LPCSTR mImportNames[] = {
    "GetFileVersionInfoA", "GetFileVersionInfoByHandle", "GetFileVersionInfoExA", "GetFileVersionInfoExW",
    "GetFileVersionInfoSizeA", "GetFileVersionInfoSizeExA", "GetFileVersionInfoSizeExW", "GetFileVersionInfoSizeW",
    "GetFileVersionInfoW", "VerFindFileA", "VerFindFileW", "VerInstallFileA", "VerInstallFileW", "VerQueryValueA",
    "VerQueryValueW"
};
UINT_PTR mProcs[_countof(mImportNames)] = {0};

static HMODULE LoadOriginalVersionDll(wchar_t* dll_rel_path) {
    wchar_t systemPath[MAX_PATH];
    wchar_t fullPath[MAX_PATH];

    UINT size = GetSystemDirectoryW(systemPath, MAX_PATH);
    if (size == 0 || size >= MAX_PATH) return NULL;

    lstrcpynW(fullPath, systemPath, MAX_PATH);
    lstrcatW(fullPath, dll_rel_path);

    return LoadLibraryW(fullPath);
}

BOOL dll_wrap_init() {
    hInstOrigDll = LoadOriginalVersionDll(L"\\version.dll");
    if (!hInstOrigDll) return FALSE;
    for (size_t i = 0; i < _countof(mImportNames); i++) {
        mProcs[i] = (UINT_PTR)GetProcAddress(hInstOrigDll, mImportNames[i]);
    }
    return TRUE;
}

BOOL dll_wrap_free() {
    return FreeLibrary(hInstOrigDll);
}

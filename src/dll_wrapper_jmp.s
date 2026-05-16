.intel_syntax noprefix

.section .text
.global _GetFileVersionInfoA, _GetFileVersionInfoByHandle, _GetFileVersionInfoExA, _GetFileVersionInfoExW
.global _GetFileVersionInfoSizeA, _GetFileVersionInfoSizeExA, _GetFileVersionInfoSizeExW, _GetFileVersionInfoSizeW
.global _GetFileVersionInfoW, _VerFindFileA, _VerFindFileW, _VerInstallFileA, _VerInstallFileW, _VerQueryValueA
.global _VerQueryValueW

_GetFileVersionInfoA:
    jmp _mProcs[0*4]
_GetFileVersionInfoByHandle:
    jmp _mProcs[1*4]
_GetFileVersionInfoExA:
    jmp _mProcs[2*4]
_GetFileVersionInfoExW:
    jmp _mProcs[3*4]
_GetFileVersionInfoSizeA:
    jmp _mProcs[4*4]
_GetFileVersionInfoSizeExA:
    jmp _mProcs[5*4]
_GetFileVersionInfoSizeExW:
    jmp _mProcs[6*4]
_GetFileVersionInfoSizeW:
    jmp _mProcs[7*4]
_GetFileVersionInfoW:
    jmp _mProcs[8*4]
_VerFindFileA:
    jmp _mProcs[9*4]
_VerFindFileW:
    jmp _mProcs[10*4]
_VerInstallFileA:
    jmp _mProcs[11*4]
_VerInstallFileW:
    jmp _mProcs[12*4]
_VerQueryValueA:
    jmp _mProcs[13*4]
_VerQueryValueW:
    jmp _mProcs[14*4]

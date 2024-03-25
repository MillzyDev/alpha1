#include <windows.h>

#include "winhttp.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
[[maybe_unused]] BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved) {
    if (fdw_reason != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(hinst_dll);
    init_proxy();

    // TODO: Check if unity
    // TODO: load modloader

    return TRUE;
}
#pragma clang diagnostic pop
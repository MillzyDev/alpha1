#include <windows.h>

#include <filesystem>

#include "winhttp.hpp"
#include "loader.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"
[[maybe_unused]] BOOL WINAPI DllMain(HINSTANCE hinst_dll, DWORD fdw_reason, LPVOID lpv_reserved) {
    if (fdw_reason != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(hinst_dll);
    init_proxy();

    std::filesystem::path install_dir;
    if (is_current_process_compatible(install_dir)) {
        load_alpha1(install_dir);
    }

    return TRUE;
}
#pragma clang diagnostic pop
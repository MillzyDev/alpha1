#include "loader.hpp"

#include <filesystem>

#include <windows.h>

bool is_current_process_compatible(std::filesystem::path &process_dir) {
    char main_module[MAX_PATH];
    GetModuleFileNameA(nullptr, main_module, MAX_PATH);

    std::filesystem::path main_process(main_module);
    std::filesystem::path main_dir = main_process.parent_path();
    std::string stem = main_process.stem().string();

    std::filesystem::path data_dir = main_dir / std::string(stem).append("_Data");
    if (!exists(data_dir)) {
        return false;
    }

    std::filesystem::path metadata = data_dir / "il2cpp_data" / "Metadata" / "global-metadata.dat";
    if (!exists(metadata)) {
        return false;
    }

    process_dir = main_dir;
    return true;
}

void load_alpha1(std::filesystem::path process_dir) {
    std::filesystem::path modloader_dll = process_dir / "alpha1" / "alpha1.dll";
    HMODULE modloader = LoadLibraryExW(modloader_dll.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);

    FARPROC init_func = GetProcAddress(modloader, "alpha1_init");
    init_func();
}
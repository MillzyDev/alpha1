#include "modloader_internal.hpp"
#include "modloader.hpp"

std::vector<alpha1::library> load_libs(const std::filesystem::path &libs_dir) {
    std::vector<alpha1::library> libs;

    for (const auto& file_entry : std::filesystem::directory_iterator(libs_dir)) {
        if (!file_entry.is_regular_file() || file_entry.path().extension() != "dll")
            continue;

        const wchar_t *module_path = file_entry.path().c_str();
        if (!GetModuleHandleW(module_path)) {
            HMODULE lib_handle = LoadLibraryW(module_path);

            alpha1::library library(
                lib_handle,
                file_entry.path().filename().string(),
                lib_handle ? NULL : GetLastError()
            );

            libs.push_back(library);
        }
    }

    return libs;
}

std::vector<alpha1::mod> load_mods(const std::filesystem::path &mods_dir) {
    std::vector<alpha1::mod> mods;

    for (const auto& file_entry : std::filesystem::directory_iterator(mods_dir)) {
        if (!file_entry.is_regular_file() || file_entry.path().extension() != "dll")
            continue;

        const wchar_t *module_path = file_entry.path().c_str();
        if (!GetModuleHandleW(module_path)) {
            HMODULE mod_handle = LoadLibraryW(module_path);

            auto setup_func = reinterpret_cast<alpha1::setup_func>(GetProcAddress(mod_handle, "setup"));
            auto load_func = reinterpret_cast<alpha1::load_func>(GetProcAddress(mod_handle, "load"));

            alpha1::mod_info mod_info{};
            setup_func(mod_info);

            alpha1::mod mod(
                mod_handle,
                file_entry.path().filename().string(),
                mod_handle ? NULL : GetLastError(),
                mod_info,
                setup_func,
                load_func
            );

            mods.push_back(mod);
        }
    }

    return mods;
}
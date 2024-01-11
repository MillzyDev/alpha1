#include <algorithm>

#include "modloader_internal.hpp"
#include "modloader.hpp"
#include "main.hpp"

static std::vector<alpha1::library> attempted_libs;
static std::vector<alpha1::mod> attempted_mods;

void alpha1::modloader::load_libs(const std::filesystem::path &libs_dir) {
    get_logger().info("MODLOADER | Loading libraries...");

    std::vector<alpha1::library> libs;

    for (const auto& file_entry : std::filesystem::directory_iterator{libs_dir}) {
        if (!file_entry.is_regular_file() || file_entry.path().extension().string() != ".dll") {
            continue;
        }

        const wchar_t *module_path = file_entry.path().c_str();
        std::string filename = file_entry.path().filename().string();

        HMODULE lib_handle = LoadLibraryW(module_path);

        alpha1::library library(
            lib_handle,
            filename,
            lib_handle ? NULL : GetLastError()
        );

        attempted_libs.push_back(library);

        if (!lib_handle)
            get_logger().error("MODLOADER | Library failed to load: {}", filename);
        else
            get_logger().info("MODLOADER | Library loaded: {}", filename);
    }

    get_logger().info("MODLOADER | Successfully loaded ({}) libraries. ({} failed)", get_loaded_libraries().size(), get_failed_libraries().size());
}

void alpha1::modloader::load_mods(const std::filesystem::path &mods_dir) {
    get_logger().info("MODLOADER | Loading mods...");

    std::vector<alpha1::mod> mods;

    for (const auto& file_entry : std::filesystem::directory_iterator(mods_dir)) {
        if (!file_entry.is_regular_file() || file_entry.path().extension().string() != ".dll")
            continue;

        const wchar_t *module_path = file_entry.path().c_str();
        std::string filename = file_entry.path().filename().string();

        HMODULE mod_handle = LoadLibraryW(module_path);

        alpha1::setup_func setup_func = nullptr;
        alpha1::load_func load_func = nullptr;

        DWORD error = 0;

        if (mod_handle) {
            setup_func = reinterpret_cast<alpha1::setup_func>(GetProcAddress(mod_handle, "setup"));
            DWORD setup_error = setup_func ? 0 : GetLastError();

            load_func = reinterpret_cast<alpha1::load_func>(GetProcAddress(mod_handle, "load"));
            DWORD load_error = load_func ? 0 : GetLastError();

            if (!setup_func || !load_func) {
                get_logger().error("MODLOADER | {} does not export the required functions. "
                                   "Ensure that both setup() and load() have C linkage and are marked with the dllexport attribute.",
                                   filename);
                get_logger().error("MODLOADER | {} setup(mod_info) address: {}, error: {}", filename, reinterpret_cast<void *>(setup_func), setup_error);
                get_logger().error("MODLOADER | {} load() address: {}, error: {}", filename, reinterpret_cast<void *>(load_func), load_error);
            }
        }
        else {
            error = GetLastError();
            get_logger().error("MODLOADER | Failed to load {} code {}", filename, error);
        }

        alpha1::mod_info mod_info{};
        setup_func(mod_info);

        alpha1::mod mod(
            mod_handle,
            file_entry.path().filename().string(),
            error,
            mod_info,
            setup_func,
            load_func
        );

        if (mod_handle && setup_func && load_func) {
            get_logger().info("MODLOADER | Successfully loaded {}|v{}", mod_info.name, mod_info.version);
        }

        attempted_mods.push_back(mod);
    }

    get_logger().info("MODLOADER | Successfully loaded ({}) mods. ({} failed)", get_loaded_mods().size(), get_failed_mods().size());
}

std::vector<alpha1::library> alpha1::modloader::get_libraries() {
    return attempted_libs;
}

std::vector<alpha1::library> alpha1::modloader::get_loaded_libraries() {
    static std::vector<alpha1::library> loaded_libraries = {};

    if (loaded_libraries.empty())
        std::copy_if(attempted_libs.begin(),
                     attempted_libs.end(),
                     std::back_inserter(loaded_libraries),
                     [](const alpha1::library &lib) {
            return lib.handle && !lib.error; // non-null handle and no errors
        });

    return loaded_libraries;
}

std::vector<alpha1::library> alpha1::modloader::get_failed_libraries() {
    static std::vector<alpha1::library> failed_libraries = {};

    if (failed_libraries.empty())
        std::copy_if(attempted_libs.begin(),
                     attempted_libs.end(),
                     std::back_inserter(failed_libraries),
                     [](const alpha1::library &lib) {
            return !lib.handle || lib.error; // null handle or an error occurred
        });

    return failed_libraries;
}

std::vector<alpha1::mod> alpha1::modloader::get_mods() {
    return attempted_mods;
}

std::vector<alpha1::mod> alpha1::modloader::get_loaded_mods() {
    static std::vector<alpha1::mod> loaded_mods = {};

    if (loaded_mods.empty()) {
        std::copy_if(attempted_mods.begin(),
                     attempted_mods.end(),
                     std::back_inserter(loaded_mods),
                     [](const alpha1::mod &mod) {
            return mod.handle && !mod.error;
        });
    }

    return loaded_mods;
}

std::vector<alpha1::mod> alpha1::modloader::get_failed_mods() {
    static std::vector<alpha1::mod> failed_mods = {};

    if (failed_mods.empty())
        std::copy_if(attempted_mods.begin(),
                     attempted_mods.end(),
                     std::back_inserter(failed_mods),
                     [](const alpha1::mod &mod) {
            return !mod.handle || mod.error;
        });

    return failed_mods;
}

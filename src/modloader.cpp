#include "modloader_internal.hpp"
#include "modloader.hpp"
#include "main.hpp"

std::vector<alpha1::library> load_libs(const std::filesystem::path &libs_dir) {
    get_logger().info("Loading libraries...");

    std::vector<alpha1::library> libs;

    for (const auto& file_entry : std::filesystem::directory_iterator(libs_dir)) {
        if (!file_entry.is_regular_file() || file_entry.path().extension() != "dll")
            continue;

        const wchar_t *module_path = file_entry.path().c_str();
        std::string filename = file_entry.path().filename().string();
        get_logger().info("Attempting to load {}", filename);

        HMODULE lib_handle = LoadLibraryW(module_path);

        if (!lib_handle)
            get_logger().error("Failed to load {}", filename);
        else
            get_logger().info("Successfully loaded {}", filename);

        alpha1::library library(
            lib_handle,
            filename,
            lib_handle ? NULL : GetLastError()
        );

        libs.push_back(library);
    }

    get_logger().info("Successfully loading ({}) libraries!", libs.size());
    return libs;
}

std::vector<alpha1::mod> load_mods(const std::filesystem::path &mods_dir) {
    get_logger().info("Loading mods...");

    std::vector<alpha1::mod> mods;

    for (const auto& file_entry : std::filesystem::directory_iterator(mods_dir)) {
        if (!file_entry.is_regular_file() || file_entry.path().extension() != "dll")
            continue;

        const wchar_t *module_path = file_entry.path().c_str();
        std::string filename = file_entry.path().filename().string();
        get_logger().info("Attempting to load {}", filename);

        HMODULE mod_handle = LoadLibraryW(module_path);

        auto setup_func = reinterpret_cast<alpha1::setup_func>(GetProcAddress(mod_handle, "setup"));
        auto load_func = reinterpret_cast<alpha1::load_func>(GetProcAddress(mod_handle, "load"));

        if (!mod_handle)
            get_logger().error("Failed to load {}", filename);
        else
            get_logger().info("Successfully loaded {}", filename);

        alpha1::mod_info mod_info{};
        setup_func(mod_info);
        get_logger().info("Finished setup for {} v{}.", mod_info.name, mod_info.version);

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

    get_logger().info("Successfully loaded ({}) mods.", mods.size());
    return mods;
}
#include "modloader_internal.hpp"
#include "files.hpp"
#include "logger.hpp"

#include <windows.h>

void create_paths() {
    if (!exists(get_logs_dir()))
        std::filesystem::create_directory(get_logs_dir());
    if (!exists(get_libs_dir()))
        std::filesystem::create_directory(get_libs_dir());
    if (!exists(get_user_data_dir()))
        std::filesystem::create_directory(get_user_data_dir());
    if (!exists(get_mods_dir()))
        std::filesystem::create_directory(get_mods_dir());
}

ALPHA1_API [[maybe_unused]] void modloader_init() {
    create_paths();
    alpha1::init_logger(true, true);

    alpha1::log(alpha1::log_level::INFO, "alpha1", "Hello world!");

    load_libs(get_libs_dir());

    MessageBoxA(nullptr, "Modloader loaded!", "Hi from alpha1!", MB_OK);
}
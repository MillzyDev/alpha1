#include "modloader_internal.hpp"
#include "files.hpp"
#include "main.hpp"
#include "hooks.hpp"

#include <windows.h>

alpha1::logger &get_logger() {
    static auto logger = alpha1::logger({"alpha1", "0.1.0" });
    return logger;
}

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

    alpha1::init_logger(false, true);
    get_logger().info("Initialised logger.");

    alpha1::modloader::attempted_libs = alpha1::modloader::load_libs(get_libs_dir());

    install_hooks();
}
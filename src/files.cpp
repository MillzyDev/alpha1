#include "files.hpp"

#include <windows.h>

#define ALPHA1_DIR_NAME "alpha1"

static std::filesystem::path base_dir;

struct Files {
    Files() {
        wchar_t exe_name[MAX_PATH];
        (void)GetModuleFileNameW(nullptr, exe_name, MAX_PATH);
        std::filesystem::path exe_path = exe_name;
        base_dir = exe_path.parent_path();
    }
};

[[maybe_unused]] static Files files;

std::filesystem::path get_libs_dir() {
    static std::filesystem::path libs_dir = base_dir / ALPHA1_DIR_NAME / "libs";
    return libs_dir;
}

std::filesystem::path get_mods_dir() {
    static std::filesystem::path mods_dir = base_dir / ALPHA1_DIR_NAME / "mods";
    return mods_dir;
}

std::filesystem::path get_alpha1_dir() {
    static std::filesystem::path alpha1_dir = base_dir / ALPHA1_DIR_NAME;
    return alpha1_dir;
}

std::filesystem::path get_user_data_dir() {
    static std::filesystem::path user_data_dir = base_dir / ALPHA1_DIR_NAME / "user_data";
    return user_data_dir;
}

std::filesystem::path get_game_dir() {
    return base_dir;
}

std::filesystem::path get_logs_dir() {
    static std::filesystem::path logs_dir = base_dir / ALPHA1_DIR_NAME / "logs";
    return logs_dir;
}
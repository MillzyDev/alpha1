#pragma once

#include <vector>
#include <filesystem>

#include "modloader.hpp"

namespace alpha1::modloader {
    static std::vector<alpha1::library> attempted_libs = {};
    static std::vector<alpha1::mod> attempted_mods = {};

    std::vector<alpha1::library> load_libs(const std::filesystem::path &libs_dir);
    std::vector<alpha1::mod> load_mods(const std::filesystem::path &mods_dir);
}
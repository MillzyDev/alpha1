#pragma once

#include <vector>
#include <filesystem>

#include "modloader.hpp"

namespace alpha1::modloader {
    void load_libs(const std::filesystem::path &libs_dir);
    void load_mods(const std::filesystem::path &mods_dir);
}
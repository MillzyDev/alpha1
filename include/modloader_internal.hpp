#pragma once

#include <vector>
#include <filesystem>

#include "modloader.hpp"

std::vector<alpha1::library> load_libs(const std::filesystem::path &libs_dir);
std::vector<alpha1::mod> loads_mods(const std::filesystem::path &mods_dir);
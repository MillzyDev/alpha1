#pragma once

#include <vector>
#include <filesystem>

#include "modloader.hpp"

std::vector<alpha1::Library> load_libs(const std::filesystem::path &libs_dir);
std::vector<alpha1::Mod> loads_mods(const std::filesystem::path &mods_dir);
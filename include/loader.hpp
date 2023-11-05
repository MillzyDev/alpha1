#pragma once

#include <filesystem>
#include <vector>
#include <windows.h>

std::vector<HMODULE> load_libs(std::filesystem::path libs_dir);
std::vector<HMODULE> load_mods(std::filesystem::path mods_dir);
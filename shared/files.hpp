#pragma once

#include <filesystem>

#ifdef ALPHA1_EXPORT_SYMBOLS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT __declspec(dllimport)
#endif

ALPHA1_EXPORT std::filesystem::path get_libs_dir();
ALPHA1_EXPORT std::filesystem::path get_mods_dir();
ALPHA1_EXPORT std::filesystem::path get_alpha1_dir();
ALPHA1_EXPORT std::filesystem::path get_user_data_dir();
ALPHA1_EXPORT std::filesystem::path get_game_dir();
ALPHA1_EXPORT std::filesystem::path get_logs_dir();


#pragma once

#include <filesystem>

#include "logger.hpp"

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    ALPHA1_EXPORT std::filesystem::path get_base_dir();
    ALPHA1_EXPORT std::filesystem::path get_alpha1_dir();
    ALPHA1_EXPORT std::filesystem::path get_mods_dir();
    ALPHA1_EXPORT std::filesystem::path get_libs_dir();
    ALPHA1_EXPORT std::filesystem::path get_user_data_dir();
    ALPHA1_EXPORT std::filesystem::path get_logs_dir();

#ifdef ALPHA1_DO_EXPORTS
    void create_logs_directory();
    void create_directories(::alpha1::logger &logger);
#endif
}

#undef ALPHA1_EXPORT
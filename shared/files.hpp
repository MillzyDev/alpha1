#pragma once

#include <filesystem>

#include "logger.hpp"

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    /**
     * Constructs and gets the path to the target game's installation directory.
     * @return The path to the target game's installation directory.
     */
    ALPHA1_EXPORT std::filesystem::path get_base_dir();

    /**
     * Constructs and gets the path to the directory containing alpha1.dll.
     * @return The path to the directory containing alpha1.dll.
     */
    ALPHA1_EXPORT std::filesystem::path get_alpha1_dir();

    /**
     * Constructs and gets the path to the mods directory.
     * @return The path to the mods directory.
     */
    ALPHA1_EXPORT std::filesystem::path get_mods_dir();

    /**
     * Construct and gets the path to the libraries directory.
     * @return The path to the libraries directory.
     */
    ALPHA1_EXPORT std::filesystem::path get_libs_dir();

    /**
     * Constructs and gets the path to the user data directory.
     * @return The path to the user data directory.
     */
    ALPHA1_EXPORT std::filesystem::path get_user_data_dir();

    /**
     * Construct and gets the path to the logs directory.
     * @return The path to the logs directory.
     */
    ALPHA1_EXPORT std::filesystem::path get_logs_dir();

#ifdef ALPHA1_DO_EXPORTS
    void create_logs_directory();
    void create_directories(::alpha1::logger &logger);
#endif
}

#undef ALPHA1_EXPORT
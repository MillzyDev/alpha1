#pragma once

#include <windows.h>
#include <string>
#include <vector>

#define ALPHA1_API extern "C" __declspec(dllexport)

#ifdef ALPHA1_EXPORT_SYMBOLS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT __declspec(dllimport)
#endif

namespace alpha1 {
    struct library {
        HMODULE handle;
        std::string name;
        DWORD error;
    };

    struct mod_info {
        std::string name;
        std::string version;
    };

    typedef void (*setup_func)(mod_info &info);
    typedef void (*load_func)();

    struct mod {
        HMODULE handle;
        std::string name;
        DWORD error;
        mod_info info;
        setup_func setup;
        load_func load;
    };
}

namespace alpha1::modloader {
    ALPHA1_EXPORT std::vector<alpha1::library> get_libraries();
    ALPHA1_EXPORT std::vector<alpha1::library> get_loaded_libraries();
    ALPHA1_EXPORT std::vector<alpha1::library> get_failed_libraries();

    ALPHA1_EXPORT std::vector<alpha1::mod> get_mods();
    ALPHA1_EXPORT std::vector<alpha1::mod> get_loaded_mods();
    ALPHA1_EXPORT std::vector<alpha1::mod> get_failed_mods();
}

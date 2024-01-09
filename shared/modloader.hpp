#pragma once

#include <windows.h>
#include <string>
#include <vector>

#define ALPHA1_API extern "C" __declspec(dllexport)

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
    std::vector<alpha1::library> get_libraries();
    std::vector<alpha1::library> get_loaded_libraries();
    std::vector<alpha1::library> get_failed_libraries();

    std::vector<alpha1::mod> get_mods();
    std::vector<alpha1::mod> get_loaded_mods();
    std::vector<alpha1::mod> get_failed_mods();
}
#pragma once

#include <windows.h>

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
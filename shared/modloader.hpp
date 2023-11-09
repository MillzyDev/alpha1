#pragma once

#include <windows.h>

#define ALPHA1_API extern "C" __declspec(dllexport)

namespace alpha1 {
    struct Library {
        HMODULE handle;
        const wchar_t *name;
        DWORD error;
    };

    struct ModInfo {
        wchar_t *name;
        wchar_t *version;
    };

    typedef void (*setup_func)(ModInfo &info);
    typedef void (*load_func)();

    struct Mod {
        HMODULE handle;
        const wchar_t *name;
        DWORD error;
        ModInfo info;
        setup_func setup;
        load_func load;
    };
}
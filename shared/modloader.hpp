#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include <windows.h>

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    typedef void (*load_t)();
    typedef void (*start_t)();
    typedef void (*scene_loaded_t)(int32_t scene_handle, int32_t mode);
    typedef void (*scene_unloaded_t)(int32_t scene_handle);
    typedef void (*quit_t)();

    struct mod_info {
        std::string name;
        std::string version;
        std::string author;
    };

    struct mod_metadata {
        std::filesystem::path filepath;
        HMODULE handle;
        ::alpha1::mod_info info;
        ::alpha1::load_t load_func;
        ::alpha1::start_t start_func;
        ::alpha1::scene_loaded_t scene_loaded_func;
        ::alpha1::scene_unloaded_t scene_unloaded_func;
        ::alpha1::quit_t quit_func;
    };

    struct library_metadata {
        std::filesystem::path filepath;
        HMODULE handle;
    };

    struct failed_library {
        std::filesystem::path filepath;
        DWORD error_code;
        std::string error_message;
    };

    void add_mod(::alpha1::mod_metadata metadata);
    void add_library(::alpha1::library_metadata metadata);
    void add_failed_mod(::alpha1::failed_library mod);
    void add_failed_library(::alpha1::failed_library library);

    class ALPHA1_EXPORT modloader {
        friend void add_mod(::alpha1::mod_metadata metadata);
        friend void add_library(::alpha1::library_metadata metadata);
        friend void add_failed_mod(::alpha1::failed_library mod);
        friend void add_failed_library(::alpha1::failed_library library);

    private:
        static std::vector<::alpha1::mod_metadata> loaded_mods;
        static std::vector<::alpha1::library_metadata> loaded_libraries;
        static std::vector<::alpha1::failed_library> failed_mods;
        static std::vector<::alpha1::failed_library> failed_libraries;

    public:
        [[nodiscard]] static bool get_mod_info(std::string mod_name, ::alpha1::mod_metadata *metadata);
        [[nodiscard]] static std::vector<::alpha1::mod_metadata> get_mods();
        [[nodiscard]] static std::vector<::alpha1::library_metadata> get_libraries();
        [[nodiscard]] static std::vector<::alpha1::failed_library> get_failed_mods();
        [[nodiscard]] static std::vector<::alpha1::failed_library> get_failed_libraries();
    };
}
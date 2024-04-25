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

    std::vector<::alpha1::start_t> get_start_callbacks();
    std::vector<::alpha1::scene_loaded_t> get_scene_loaded_callbacks();
    std::vector<::alpha1::scene_unloaded_t> get_scene_unloaded_callbacks();
    std::vector<::alpha1::quit_t> get_quit_callbacks();

    void add_start_callback(::alpha1::start_t callback);
    void add_scene_loaded_callback(::alpha1::scene_loaded_t callback);
    void add_scene_unloaded_callback(::alpha1::scene_unloaded_t callback);
    void add_quit_callback(::alpha1::quit_t callback);

    class ALPHA1_EXPORT modloader {
        friend void add_mod(::alpha1::mod_metadata metadata);
        friend void add_library(::alpha1::library_metadata metadata);
        friend void add_failed_mod(::alpha1::failed_library mod);
        friend void add_failed_library(::alpha1::failed_library library);

        friend std::vector<::alpha1::start_t> get_start_callbacks();
        friend std::vector<::alpha1::scene_loaded_t> get_scene_loaded_callbacks();
        friend std::vector<::alpha1::scene_unloaded_t> get_scene_unloaded_callbacks();
        friend std::vector<::alpha1::quit_t> get_quit_callbacks();
        friend void add_start_callback(::alpha1::start_t callback);
        friend void add_scene_loaded_callback(::alpha1::scene_loaded_t callback);
        friend void add_scene_unloaded_callback(::alpha1::scene_unloaded_t callback);
        friend void add_quit_callback(::alpha1::quit_t callback);


    private:
        static std::vector<::alpha1::mod_metadata> loaded_mods;
        static std::vector<::alpha1::library_metadata> loaded_libraries;
        static std::vector<::alpha1::failed_library> failed_mods;
        static std::vector<::alpha1::failed_library> failed_libraries;

        static std::vector<::alpha1::start_t> start_callbacks;
        static std::vector<::alpha1::scene_loaded_t> scene_loaded_callbacks;
        static std::vector<::alpha1::scene_unloaded_t> scene_unloaded_callbacks;
        static std::vector<::alpha1::quit_t> quit_callbacks;

    public:
        /**
         * Searches for a loaded mod metadata with the given name
         * @param mod_name Name of the mod to search for.
         * @param metadata The metadata of the mod if found. If the mod metadata could not be found, it will equate to nullptr.
         * @return Whether the mod was able to be found.
         */
        [[nodiscard]] static bool get_mod_info(std::string mod_name, ::alpha1::mod_metadata *metadata);

        /**
         * Gets all metadata of mods that were successfully loaded.
         * @return A vector of successfully loaded mods.
         */
        [[nodiscard]] static std::vector<::alpha1::mod_metadata> get_mods();

        /**
         * Gets all metadata of libraries that were successfully loaded.
         * @return A vector of successfully loaded modlibraries.
         */
        [[nodiscard]] static std::vector<::alpha1::library_metadata> get_libraries();

        /**
         * Gets info for all mods that failed to load.
         * @return Information regarding the failed mod.
         */
        [[nodiscard]] static std::vector<::alpha1::failed_library> get_failed_mods();

        /**
         * Gets info for all libraries that failed to load.
         * @return Information regarding the failed library.
         */
        [[nodiscard]] static std::vector<::alpha1::failed_library> get_failed_libraries();
    };
}

#undef ALPHA1_EXPORT
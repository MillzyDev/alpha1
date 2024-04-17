#include "loading.hpp"
#include "files.hpp"
#include "utils.hpp"
#include "modloader.hpp"

#define SHARED_LIB_EXT ".dll"

typedef ::alpha1::mod_info (*get_info_t)();

namespace alpha1 {
    void load_libraries(::alpha1::logger &logger) {
        std::filesystem::path libs_dir = ::alpha1::get_libs_dir();
        logger.info("Loading libraries in {0}", libs_dir.string());

        for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(libs_dir)) {
            std::error_code error_code;
            std::filesystem::path path = entry.path();

            if (entry.is_directory(error_code)) {
                continue;
            }

            if (error_code) {
                logger.error("Error validating {0}", path.string());
                logger.error("Code: {0} - {1}", error_code.value(), error_code.message());
                continue;
            }

            if (path.extension() != SHARED_LIB_EXT) {
                continue;
            }

            HMODULE module = GetModuleHandleA(path.string().c_str()); // check if its already loaded
            if (!module) {
                SetLastError(0);

                module = LoadLibraryExW(path.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
                if (!module) {
                    DWORD sys_error = GetLastError();
                    std::string error_message = get_error_message(sys_error);

                    logger.error("Failed to load library: {0}", path.stem().string());
                    logger.error("Code: {0} - {1}", sys_error, get_error_message(sys_error));

                    ::alpha1::add_failed_library({path, sys_error, error_message});
                    continue;
                }
            }

            ::alpha1::add_library({path, module});
            logger.info("Loaded library: {0}", path.stem().string());
        }

        logger.info("Finished loading libraries.");
    }

    void load_mods(::alpha1::logger &logger) {
        std::filesystem::path mods_dir = ::alpha1::get_mods_dir();
        logger.info("Loading mods in {0}", mods_dir.string());

        for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(mods_dir)) {
            std::error_code error_code;
            std::filesystem::path path = entry.path();

            if (entry.is_directory(error_code)) {
                continue;
            }

            if (error_code) {
                logger.error("Error validating {0}", path.string());
                logger.error("Code: {0} - {1}", error_code.value(), error_code.message());
                continue;
            }

            if (path.extension() != SHARED_LIB_EXT) {
                continue;
            }

            HMODULE module = GetModuleHandleA(path.string().c_str());
            if (!module) {
                SetLastError(0);

                module = LoadLibraryExW(path.c_str(), nullptr, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR);
                if (!module) {
                    DWORD sys_error = GetLastError();
                    std::string error_message = get_error_message(sys_error);

                    logger.error("Failed to load mod: {0}", path.stem().string());
                    logger.error("Code: {0} - {1}", sys_error, get_error_message(sys_error));

                    ::alpha1::add_failed_mod({path, sys_error, error_message});
                    continue;
                }
            }

            FARPROC get_info_addr = GetProcAddress(module, "get_info");
            if (!get_info_addr) {
                DWORD sys_error = GetLastError();
                std::string error_message = get_error_message(sys_error);

                logger.error("Failed to load mod: {0}", path.stem().string());
                logger.error("Unable to get address of function get_info.");
                logger.error("Code: {0} - {1}", sys_error, error_message);

                ::alpha1::add_failed_mod({path, sys_error, error_message});
                continue;
            }

            get_info_t get_info = reinterpret_cast<get_info_t>(get_info_addr);
            ::alpha1::mod_info info = get_info();

            load_t load = reinterpret_cast<load_t>(GetProcAddress(module, "load"));
            start_t start = reinterpret_cast<start_t>(GetProcAddress(module, "start"));
            scene_loaded_t scene_loaded = reinterpret_cast<scene_loaded_t >(GetProcAddress(module, "scene_loaded"));
            scene_unloaded_t scene_unloaded = reinterpret_cast<scene_unloaded_t>(GetProcAddress(module, "scene_unloaded"));
            quit_t quit = reinterpret_cast<quit_t>(GetProcAddress(module, "quit"));
            SetLastError(0);

            ::alpha1::add_mod({
                path,
                module,
                info,
                load,
                start,
                scene_loaded,
                scene_unloaded,
                quit
            });

            load();
            logger.info("Loaded mod: {0} v{1} ({2})", info.name, info.version, info.author);
        }

        size_t loaded_mods = ::alpha1::modloader::get_mods().size();
        size_t failed_mods = ::alpha1::modloader::get_failed_mods().size();
        logger.info("Successfully loaded {0} mods! ({1} failed)", loaded_mods, failed_mods);
    }
}
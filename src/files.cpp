#include <optional>
#include <windows.h>

#include "files.hpp"
#include "utils.hpp"

#define SUBDIR_GETTER(name, subdir)                                               \
std::filesystem::path name() {                                                  \
    static std::filesystem::path dir_path = ::alpha1::get_base_dir() / subdir;    \
    return dir_path;                                                            \
}

#define ALPHA1_DIR "alpha1"
#define MODS_DIR "mods"
#define LIBS_DIR "libs"
#define DATA_DIR "user_data"

namespace alpha1 {
    std::filesystem::path get_base_dir() {
        static std::optional<std::filesystem::path> base_dir;
        if (base_dir.has_value()) {
            return base_dir.value();
        }

        SetLastError(0);
        char main_process[MAX_PATH];
        GetModuleFileNameA(nullptr, main_process, MAX_PATH);
        DISPLAY_ABORT_UNLESS(GetLastError())

        base_dir = std::filesystem::path(main_process).parent_path();
        return base_dir.value();
    }

    SUBDIR_GETTER(get_alpha1_dir, ALPHA1_DIR)
    SUBDIR_GETTER(get_mods_dir, MODS_DIR)
    SUBDIR_GETTER(get_libs_dir, LIBS_DIR)
    SUBDIR_GETTER(get_user_data_dir, DATA_DIR)
    SUBDIR_GETTER(get_logs_dir, ALPHA1_DIR / "logs")

    void create_logs_directory() {
        static std::filesystem::path logs_dir = get_logs_dir();
        if (!exists(logs_dir)) {
            std::error_code error_code;
            std::filesystem::create_directories(logs_dir, error_code);

            if (error_code) {
                DISPLAY_ERROR_ABORT(error_code.value());
            }
        }
    }

    void create_directories() {
        static std::filesystem::path required_dirs[] = {
                get_mods_dir(),
                get_libs_dir(),
                get_user_data_dir()
        };

        for (std::filesystem::path path : required_dirs) {
            if (!exists(path)) {
                std::error_code error_code;
                std::filesystem::create_directories(path, error_code);

                if (error_code) {
                    DISPLAY_ERROR_ABORT(error_code.value());
                }
            }
        }
    }
}
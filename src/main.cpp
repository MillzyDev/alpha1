#include "modloader_internal.hpp"
#include "files.hpp"

#include <windows.h>

void create_paths() {

}

ALPHA1_API [[maybe_unused]] void modloader_init() {
    load_libs(get_libs_dir());

    MessageBoxA(nullptr, "Modloader loaded!", "Hi from alpha1!", MB_OK);
}
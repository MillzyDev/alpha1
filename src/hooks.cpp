#include "hooks.hpp"
#include "main.hpp"
#include "modloader_internal.hpp"
#include "files.hpp"
#include "dobby.h"

#include <windows.h>

int (*orig_il2cpp_init)(const char *domain_name);

int hook_il2cpp_init(const char *domain_name) {
    get_logger().info("Initialising in domain: {}", domain_name);
    int ret = orig_il2cpp_init(domain_name); // run original function

    // load mods
    (void)load_mods(get_mods_dir());

    return ret; // return original value
}

void install_hooks() {
    get_logger().info("Installing hooks...");

    HMODULE game_assembly = LoadLibraryA("GameAssembly.dll");
    auto il2cpp_init_func = reinterpret_cast<void *>(GetProcAddress(game_assembly, "il2cpp_init"));

    get_logger().info("Installing il2cpp_init ({}) hook...", il2cpp_init_func);

    DobbyHook(il2cpp_init_func, reinterpret_cast<void *>(hook_il2cpp_init), (reinterpret_cast<void **>(&orig_il2cpp_init)));

    get_logger().info("Installed all hooks.");
}

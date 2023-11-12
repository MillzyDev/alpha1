#include "hooks.hpp"
#include "main.hpp"
#include "modloader_internal.hpp"
#include "files.hpp"

#include "rcmp.hpp"

#include <windows.h>

void install_hooks() {
    get_logger().info("Installing hooks...");

    HMODULE game_assembly = LoadLibraryA("GameAssembly.dll");
    auto il2cpp_init_func = reinterpret_cast<void *>(GetProcAddress(game_assembly, "il2cpp_init"));

    get_logger().info("Installing il2cpp_init ({}) hook...", il2cpp_init_func);
    rcmp::hook_function<int(*)(const char *)>(il2cpp_init_func, [](auto original, const char *domain_name) {
        get_logger().info("IL2CPP initialised.");
        get_logger().info("Domain name: {}", domain_name);
        //get_logger().info("Orig returned: {}", ret);

        load_mods(get_mods_dir());

        return original(domain_name);
    });

    get_logger().info("Installed all hooks.");
}
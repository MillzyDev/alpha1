#include "hooks.hpp"
#include "main.hpp"
#include "modloader_internal.hpp"
#include "files.hpp"
#include "dobby.h"
#include "il2cpp_types.hpp"

#include <windows.h>

int (*orig_il2cpp_init)(const char *domain_name);

int hook_il2cpp_init(const char *domain_name) {
    get_logger().info("init hook: Initialising in domain: {}", domain_name);
    int ret = orig_il2cpp_init(domain_name); // run original function

    // load mods
    alpha1::modloader::attempted_mods = alpha1::modloader::load_mods(get_mods_dir());

    return ret; // return original value
}

void *il2cpp_runtime_invoke_func;
void *(*orig_il2cpp_runtime_invoke)(const MethodInfo *method, void *obj, void **params, void **exc);

void *hook_il2cpp_runtime_invoke(const MethodInfo *method, void *obj, void **params, void **exc) {
    void *ret = orig_il2cpp_runtime_invoke(method, obj, params, exc);

    if (std::string(method->name) == "Start") {
        DobbyDestroy(il2cpp_runtime_invoke_func);
        get_logger().info("runtime_invoke hook: Start method invoked, destroyed hook.");

    }

    return ret;
}

void install_hooks() {
    get_logger().info("Installing hooks...");

    HMODULE game_assembly = LoadLibraryA("GameAssembly.dll");

    auto il2cpp_init_func = reinterpret_cast<void *>(GetProcAddress(game_assembly, "il2cpp_init"));
    get_logger().info("Installing il2cpp_init ({}) hook...", il2cpp_init_func);
    DobbyHook(il2cpp_init_func, reinterpret_cast<void *>(hook_il2cpp_init), (reinterpret_cast<void **>(&orig_il2cpp_init)));

    il2cpp_runtime_invoke_func = reinterpret_cast<void *>(GetProcAddress(game_assembly, "il2cpp_runtime_invoke"));
    get_logger().info("Installing il2cpp_runtime_invoke ({}) hook...", il2cpp_runtime_invoke_func);
    DobbyHook(il2cpp_runtime_invoke_func, reinterpret_cast<void *>(hook_il2cpp_runtime_invoke), reinterpret_cast<void **>(&orig_il2cpp_runtime_invoke));

    get_logger().info("Installed all hooks.");
}

#include "hooks.hpp"
#include "main.hpp"
#include "modloader_internal.hpp"
#include "modloader.hpp"
#include "files.hpp"
#include "il2cpp_types.hpp"

#include "dobby.h"

#include <windows.h>

int (*orig_il2cpp_init)(const char *domain_name);

int hook_il2cpp_init(const char *domain_name) {
    get_logger().info("HOOK | il2cpp_init: Initialising in domain: {}", domain_name);
    int ret = orig_il2cpp_init(domain_name); // run original function

    // load mods
     alpha1::modloader::load_mods(get_mods_dir());

    return ret;
}

void *il2cpp_runtime_invoke_func;
void *(*orig_il2cpp_runtime_invoke)(const MethodInfo *method, void *obj, void **params, void **exc);

void *hook_il2cpp_runtime_invoke(const MethodInfo *method, void *obj, void **params, void **exc) {
    void *ret = orig_il2cpp_runtime_invoke(method, obj, params, exc);

    get_logger().info("HOOK | il2cpp_runtime_invoke: IL2CPP method invoked: {}", method->name);

    if (std::string(method->name) != "Start")
        return ret;

    get_logger().info("HOOK | il2cpp_runtime_invoke: Finishing mod initialisation...");

    std::vector<alpha1::mod> loaded_mods = alpha1::modloader::get_loaded_mods();
    for (const auto& mod : loaded_mods) {
        mod.load(); // call load function
    }

    get_logger().info("HOOK | il2cpp_runtime_invoke: Finished initialising mods");

    DobbyDestroy(il2cpp_runtime_invoke_func);
    get_logger().info("HOOK | il2cpp_runtime_invoke: Destroyed self.");

    return ret;
}

void install_hooks() {
    HMODULE game_assembly = LoadLibraryA("GameAssembly.dll");

    auto il2cpp_init_func = reinterpret_cast<void *>(GetProcAddress(game_assembly, "il2cpp_init"));
    get_logger().info("Installing il2cpp_init ({}) hook...", il2cpp_init_func);
    DobbyHook(il2cpp_init_func, reinterpret_cast<void *>(hook_il2cpp_init), (reinterpret_cast<void **>(&orig_il2cpp_init)));

    il2cpp_runtime_invoke_func = reinterpret_cast<void *>(GetProcAddress(game_assembly, "il2cpp_runtime_invoke"));
    get_logger().info("Installing il2cpp_runtime_invoke ({}) hook...", il2cpp_runtime_invoke_func);
    DobbyHook(il2cpp_runtime_invoke_func, reinterpret_cast<void *>(hook_il2cpp_runtime_invoke), reinterpret_cast<void **>(&orig_il2cpp_runtime_invoke));

    get_logger().info("Finished installing hooks.");
}

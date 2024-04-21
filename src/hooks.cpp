#include "hooks.hpp"
#include "hooking.hpp"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "loading.hpp"
#include "il2cpp_utils.hpp"
#include "modloader.hpp"

static ::alpha1::logger *hook_logger = nullptr;

static il2cpp_init_t il2cpp_init_orig = nullptr;

int il2cpp_init_detour(const char *domain_name) {
    int ret = il2cpp_init_orig(domain_name);

    alpha1::load_mods(*hook_logger);

    ::alpha1::hook_runtime();

    // just to be sure.
    ::alpha1::unhook(reinterpret_cast<void **>(&il2cpp_init_orig), reinterpret_cast<void *>(il2cpp_init_detour));
    return ret;
}

typedef void (*active_scene_changed_t)(int32_t previous_scene_handle, int32_t new_scene_handle, const MethodInfo *runtime_method);
typedef void (*scene_loaded_t)(int32_t scene_handle, int32_t mode, const MethodInfo *runtime_method);
typedef void (*scene_unloaded_t)(int32_t scene_handle, const MethodInfo *runtime_method);
typedef void (*quit_t)(const MethodInfo *runtime_method);

static active_scene_changed_t active_scene_changed_orig;
static scene_loaded_t scene_loaded_orig;
static scene_unloaded_t scene_unloaded_orig;
static quit_t quit_orig;

void active_scene_changed_detour(int32_t previous_scene_handle, int32_t new_scene_handle, const MethodInfo *runtime_method) {
    active_scene_changed_orig(previous_scene_handle, new_scene_handle, runtime_method);

    for (::alpha1::start_t callback : ::alpha1::get_start_callbacks()) {
        callback();
    }

    // start should only be called once, so unhook
    ::alpha1::unhook(reinterpret_cast<void **>(&active_scene_changed_orig), reinterpret_cast<void *>(active_scene_changed_detour));
}

void scene_loaded_detour(int32_t scene_handle, int32_t mode, const MethodInfo *runtime_method) {
    scene_loaded_orig(scene_handle, mode, runtime_method);

    static std::vector<::alpha1::scene_loaded_t> callbacks = ::alpha1::get_scene_loaded_callbacks();

    for (::alpha1::scene_loaded_t callback : callbacks) {
        callback(scene_handle, mode);
    }
}

void scene_unloaded_detour(int32_t scene_handle, const MethodInfo *runtime_method) {
    scene_unloaded_orig(scene_handle, runtime_method);

    static std::vector<::alpha1::scene_unloaded_t> callbacks = ::alpha1::get_scene_unloaded_callbacks();

    for (::alpha1::scene_unloaded_t callback : callbacks) {
        callback(scene_handle);
    }
}

namespace alpha1 {
    void hook_init(::alpha1::logger &logger) {
        hook_logger = &logger;

        il2cpp_init_orig = ::alpha1::il2cpp::init;
        ::alpha1::hook(reinterpret_cast<void **>(&il2cpp_init_orig), reinterpret_cast<void *>(il2cpp_init_detour));
    }

    void hook_runtime() {
        Il2CppClass *scene_manager = ::alpha1::il2cpp_utils::find_class("UnityEngine.SceneManagement", "SceneManager");
        const MethodInfo *start_target = ::alpha1::il2cpp_utils::find_method(scene_manager, "Internal_ActiveSceneChanged", 2);
        const MethodInfo *scene_load_target = ::alpha1::il2cpp_utils::find_method(scene_manager, "Internal_SceneLoaded", 2);
        const MethodInfo *scene_unload_target = ::alpha1::il2cpp_utils::find_method(scene_manager, "Internal_SceneUnloaded", 1);

        Il2CppClass *application = ::alpha1::il2cpp_utils::find_class("UnityEngine", "Application");
        const MethodInfo *quit_target = ::alpha1::il2cpp_utils::find_method(application, "Internal_ApplicationQuit", 0);

        active_scene_changed_orig = reinterpret_cast<active_scene_changed_t>(start_target->methodPointer);
        scene_loaded_orig = reinterpret_cast<::scene_loaded_t>(scene_load_target->methodPointer);
        scene_unloaded_orig = reinterpret_cast<::scene_unloaded_t>(scene_unload_target->methodPointer);
        quit_orig = reinterpret_cast<::quit_t>(quit_target->methodPointer);

        ::alpha1::hook(reinterpret_cast<void **>(&active_scene_changed_orig), reinterpret_cast<void *>(active_scene_changed_detour));
        ::alpha1::hook(reinterpret_cast<void **>(&scene_loaded_orig), reinterpret_cast<void *>(scene_loaded_detour));
        ::alpha1::hook(reinterpret_cast<void **>(&scene_unloaded_orig), reinterpret_cast<void *>(scene_unloaded_detour));
    }
}
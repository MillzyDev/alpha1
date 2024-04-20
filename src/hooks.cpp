#include "hooks.hpp"
#include "hooking.hpp"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "loading.hpp"

static ::alpha1::logger *hook_logger = nullptr;
static il2cpp_init_t il2cpp_init_orig = nullptr;

int il2cpp_init_detour(const char *domain_name) {
    int ret = il2cpp_init_orig(domain_name);

    alpha1::load_mods(*hook_logger);

    ::alpha1::hook_runtime();

    return ret;
}

namespace alpha1 {
    void hook_init(::alpha1::logger &logger) {
        hook_logger = &logger;

        il2cpp_init_orig = ::alpha1::il2cpp::init;
        hook(reinterpret_cast<void **>(&il2cpp_init_orig), reinterpret_cast<void *>(il2cpp_init_detour));
    }

    void hook_runtime() {

    }
}
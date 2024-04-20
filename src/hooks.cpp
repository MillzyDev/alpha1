#include "hooks.hpp"
#include "hooking.hpp"
#include "il2cpp.hpp"
#include "logger.hpp"

static ::alpha1::logger *hook_logger = nullptr;
static il2cpp_init_t orig = nullptr;

int il2cpp_init_detour(const char *domain_name) {
    hook_logger->info("Domain name: {0}", domain_name);
    return orig(domain_name);
}

namespace alpha1 {
    void hook_init(::alpha1::logger &logger) {
        hook_logger = &logger;
        orig = ::alpha1::il2cpp::init;
        hook(reinterpret_cast<void **>(&orig), reinterpret_cast<void *>(il2cpp_init_detour));
    }

    void hook_runtime() {

    }
}
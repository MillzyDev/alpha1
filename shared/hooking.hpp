#pragma once

#include <string>

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    /**
     * Hooks the function at the given address with the provided detour function.
     * @param target The address of the original function the hook is targeted at.
     * @param detour The address of the function to detour to when the target function is invoked.
     */
    ALPHA1_EXPORT void hook(void **target, void *detour);

    /**
     * Removes a hook on a target function.
     * @param target The address of the original function that the hook was targeted at.
     * @param detour The address of the detour to remove.
     */
    ALPHA1_EXPORT void unhook(void **target, void *detour);
}

#undef ALPHA1_EXPORT
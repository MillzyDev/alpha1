#pragma once

#include <string>

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    ALPHA1_EXPORT void hook(void **target, void *detour);

#ifdef ALPHA1_DO_EXPORTS
     void unhook(void **target, void *detour);
#endif
}

#undef ALPHA1_EXPORT
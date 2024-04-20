#include "hooking.hpp"

#include <windows.h>
#include "detours.h"

namespace alpha1 {
    void hook(void **target, void *detour) {
        // TODO: error checking
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(target, detour);
        DetourTransactionCommit();
    }

    void unhook(void **target, void *detour) {
        // TODO: error checking
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(target, detour);
        DetourTransactionCommit();
    }
}
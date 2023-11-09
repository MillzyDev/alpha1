#include "modloader.hpp"

#include <windows.h>

 ALPHA1_API [[maybe_unused]] void modloader_init() {
    MessageBoxA(nullptr, "Modloader loaded!", "Hi from alpha1!", MB_OK);
}
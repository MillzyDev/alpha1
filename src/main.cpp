#include <windows.h>

#include "files.hpp"

extern "C" __declspec(dllexport) void alpha1_init() {
    alpha1::create_logs_directory();


}
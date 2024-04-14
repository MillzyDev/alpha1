#include <windows.h>

#include "files.hpp"
#include "logger.hpp"

extern "C" __declspec(dllexport) void alpha1_init() {
    alpha1::create_logs_directory();
    alpha1::logger::initialise_logger();

    alpha1::logger my_logger({"alpha1", "0.1.0", ""});
    my_logger.info("Successfully initialised logger!");
}
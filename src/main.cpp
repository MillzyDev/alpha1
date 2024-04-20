#include <windows.h>

#include "files.hpp"
#include "logger.hpp"
#include "loading.hpp"
#include "il2cpp.hpp"

static alpha1::logger main_logger({"alpha1", "0.1.0", ""});

extern "C" __declspec(dllexport) void alpha1_init() {
    alpha1::create_logs_directory();
    alpha1::logger::initialise_logger();
    main_logger.info("Successfully initialised logger!");

    alpha1::create_directories(main_logger);

    alpha1::load_il2cpp_funcs(main_logger);

    alpha1::load_libraries(main_logger);
}
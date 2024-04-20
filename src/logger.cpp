#include <chrono>
#include <iostream>

#include "logger.hpp"
#include "files.hpp"
#include "utils.hpp"

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define WHITE "\x1b[37m"
#define YELLOW "\x1b[93m"
#define CYAN "\x1b[96m"

std::string get_timestamp() {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::string timestamp = std::format(
            "{0:%H:%M:%S}",
            std::chrono::time_point_cast<std::chrono::milliseconds>(now)
    );
    return timestamp;
}

namespace alpha1 {
    bool logger::initialised = false;
    std::ofstream logger::log_file_stream;

    void logger::initialise_logger() {
        if (logger::initialised) {
            return;
        }

        std::filesystem::path latest_log = alpha1::get_logs_dir() / "latest.log";

        // move the existing latest.log to the logs dir and rename
        if (exists(latest_log)) {
            std::error_code error_code;
            std::filesystem::file_time_type last_write = std::filesystem::last_write_time(latest_log, error_code);
            DISPLAY_ABORT_UNLESS(error_code.value());

            std::string last_log_name = std::format(
                    "alpha1_{0:%Y-%m-%d_%H-%M-%S}.log",
                    std::chrono::time_point_cast<std::chrono::milliseconds>(last_write)
                    );

            std::filesystem::path last_log_path = get_logs_dir() / last_log_name;
            std::filesystem::rename(latest_log, last_log_path);
        }

        // create log file
        logger::log_file_stream = std::ofstream(latest_log);

        // create the console
        SetLastError(0);
        bool success = AllocConsole();
        if (!success) {
            DISPLAY_ERROR_ABORT(GetLastError());
        }

        // allow the console to display colour
        HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (console_out == INVALID_HANDLE_VALUE) {
            DISPLAY_ERROR_ABORT(GetLastError());
        }

        // redirect stdout to console
        freopen("CONOUT$", "w", stdout);

        DWORD mode;
        if (!GetConsoleMode(console_out, &mode)) {
            DISPLAY_ERROR_ABORT(GetLastError());
        }

        if (!SetConsoleMode(console_out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
            DISPLAY_ERROR_ABORT(GetLastError());
        }

        logger::initialised = true;
    }

    logger::logger(struct mod_info mod_info) {
        this->mod_info = mod_info;
    }

    void logger::log_info(std::string name, std::string msg) {
        std::string timestamp = get_timestamp();

        logger::log_file_stream
            << "[" << timestamp << "] [" << name << "] " << msg << std::endl;

        std::stringstream console;
        console
            << WHITE << "["
            << GREEN << timestamp
            << WHITE << "] ["
            << CYAN << name
            << WHITE << "] "
            << msg << RESET << "\n";
        std::string console_str = console.str();

        std::cout << console_str.c_str();
    }

    void logger::log_warn(std::string name, std::string msg) {
        std::string timestamp = get_timestamp();

        logger::log_file_stream
                << "[" << timestamp << "] [" << name << "] " << msg << std::endl;

        std::stringstream console;
        console
                << YELLOW << "["
                << timestamp
                << "] ["
                << name
                << "] WARNING: "
                << msg << RESET << "\n";
        std::string console_str = console.str();

        std::cout << console_str.c_str();
    }

    void logger::log_error(std::string name, std::string msg) {
        std::string timestamp = get_timestamp();

        logger::log_file_stream
                << "[" << timestamp << "] [" << name << "] " << msg << std::endl;

        std::stringstream console;
        console
                << RED << "["
                << timestamp
                << "] ["
                << name
                << "] WARNING: "
                << msg << RESET << "\n";
        std::string console_str = console.str();

        std::cout << console_str.c_str();
    }
}

#include "logger.hpp"
#include "files.hpp"

#include <fstream>
#include <filesystem>
#include <chrono>
#include <iostream>

std::ofstream log_file_stream;
bool disable_logging;
bool use_console;

namespace alpha1 {
    void init_logger(bool no_logging, bool enable_console) {
        std::filesystem::path logs_dir = get_logs_dir();
        std::filesystem::path latest_log = logs_dir / "latest.log";

        if (exists(latest_log)) {
            std::filesystem::file_time_type file_time = std::filesystem::last_write_time(latest_log);
            auto system_time = std::chrono::clock_cast<std::chrono::system_clock>(file_time);
            auto date_time = std::chrono::current_zone()->to_local(system_time);

            std::string log_file_name = std::format("alpha1_{:%Y-%m-%d_%H-%M-%S}.log", date_time);
            std::filesystem::path full_log_file_name = logs_dir / log_file_name;

            std::filesystem::rename(latest_log, full_log_file_name);
        }

        disable_logging = no_logging;
        if (no_logging)
            return;

        log_file_stream = std::ofstream(latest_log);

        if (enable_console) {
            if (AllocConsole()) {
                freopen("CONOUT$", "w", stdout);
                use_console = true;
            }
            else {
                log(log_level::ERR,
                    "alpha1",

                    "Unable to create console. It may be the case that one already exists, "
                    "in which case alpha1 will not use it to prevent conflicts."
                );
            }
        }
    }

    void log(log_level level, const std::string& source_name, const std::string& message) {
        if (disable_logging || level == log_level::NONE) return;

        auto now = std::chrono::system_clock::now();

        std::string timestamp = std::format("{:%H:%M:%S}", now);

        std::string level_string;
        int color_attribute;

        switch (level) {
            case INFO:
                level_string = "INFO";
                color_attribute = 10;
                break;
            case ERR:
                level_string = "ERROR";
                color_attribute = 12;
                break;
            case CRITICAL:
                level_string = "CRITICAL";
                color_attribute = 12;
                break;
            case DEBUG:
                level_string = "DEBUG";
                color_attribute = 9;
                break;
            case WARNING:
                level_string = "WARN";
                color_attribute = 14;
                break;
            case NONE:
                break;
        }

        std::string full_message = std::format("[{}] [{}] [{}] {}", timestamp, source_name, level_string, message);
        log_file_stream << full_message << std::endl;
        log_file_stream.flush();

        if (use_console) {
            static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, color_attribute);
            std::cout << full_message << std::endl;
        }
    }

    ALPHA1_EXPORT logger::logger(const alpha1::mod_info& mod_info) {
        this->mod_info_ = mod_info;
    }

    ALPHA1_EXPORT void logger::log(log_level level, const std::string& message) const {
        alpha1::log(level, this->mod_info_.name, message);
    }
}
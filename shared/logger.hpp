#pragma once

#include "modloader.hpp"

#include <string>
#include <format>

namespace alpha1 {
    enum log_level {
        NONE,
        INFO,
        ERR,
        CRITICAL,
        WARNING,
        DEBUG
    };

    void init_logger(bool enable_logging, bool enable_console);
    void log(log_level level, const std::string& source_name, const std::string& message);

    class logger  {
    private:
        alpha1::mod_info mod_info_;

    public:
        explicit logger(const alpha1::mod_info& mod_info);

        void log(log_level level, const std::string& message) const;

        template<typename... Args>
        void info(std::format_string<Args...> fmt, Args &&...args);

        template<typename... Args>
        void warn(std::format_string<Args...> fmt, Args &&...args);

        template<typename... Args>
        void error(std::format_string<Args...> fmt, Args &&...args);

        template<typename... Args>
        void crit(std::format_string<Args...> fmt, Args &&...args);

        template<typename... Args>
        void debug(std::format_string<Args...> fmt, Args &&...args);
    };
}

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

    void init_logger(bool no_logging, bool enable_console);
    void log(log_level level, const std::string& source_name, const std::string& message);

    class logger  {
    private:
        alpha1::mod_info mod_info_;

    public:
        explicit logger(const alpha1::mod_info& mod_info);

        void log(log_level level, const std::string& message) const;

        template<typename... Args>
        inline void info(std::format_string<Args...> fmt, Args &&...args) {
            std::string message = std::vformat(fmt.get(), std::make_format_args(args...));
            log(log_level::INFO, message);
        }

        template<typename... Args>
        inline void warn(std::format_string<Args...> fmt, Args &&...args) {
            std::string message = std::vformat(fmt.get(), std::make_format_args(args...));
            log(log_level::WARNING, message);
        }

        template<typename... Args>
        inline void error(std::format_string<Args...> fmt, Args &&...args) {
            std::string message = std::vformat(fmt.get(), std::make_format_args(args...));
            log(log_level::ERR, message);
        }

        template<typename... Args>
        inline void crit(std::format_string<Args...> fmt, Args &&...args) {
            std::string message = std::vformat(fmt.get(), std::make_format_args(args...));
            log(log_level::CRITICAL, message);
        }

        template<typename... Args>
        inline void debug(std::format_string<Args...> fmt, Args &&...args) {
            std::string message = std::vformat(fmt.get(), std::make_format_args(args...));
            log(log_level::DEBUG, message);
        }
    };
}

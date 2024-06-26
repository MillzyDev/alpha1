#pragma once

#include <fstream>
#include <string>
#include <format>

#include "modloader.hpp"

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

namespace alpha1 {
    class ALPHA1_EXPORT logger {
    private:
        static bool initialised;
        static std::ofstream log_file_stream;

        mod_info mod_info;

        static void log_info(std::string name, std::string msg);
        static void log_warn(std::string name, std::string msg);
        static void log_error(std::string name, std::string msg);

    public:
        explicit logger(struct mod_info mod_info);
        static void initialise_logger();

        /**
         * Logs to the console at the Info level.
         * @param format A string format for the message.
         * @param args Format arguments
         */
        template<typename... Args>
        inline void info(std::format_string<Args...> format, Args &&...args) {
            std::string message = std::vformat(format.get(), std::make_format_args(args...));
            ::alpha1::logger::log_info(this->mod_info.name, message);
        }

        /**
         * Logs to the console at the Warning level.
         * @param format A string format for the message.
         * @param args Format arguments
         */
        template<typename... Args>
        inline void warning(std::format_string<Args...> format, Args &&...args) {
            std::string message = std::vformat(format.get(), std::make_format_args(args...));
            ::alpha1::logger::log_warn(this->mod_info.name, message);
        }

        /**
         * Logs to the console at the Error level.
         * @param format A string format for the message.
         * @param args Format arguments
         */
        template<typename... Args>
        inline void error(std::format_string<Args...> format, Args &&...args) {
            std::string message = std::vformat(format.get(), std::make_format_args(args...));
            ::alpha1::logger::log_error(this->mod_info.name, message);
        }
    };
}

#undef ALPHA1_EXPORT
#include <sstream>

#include "utils.hpp"

#define MESSAGE_FLAGS FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
#define LANG_ID MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)

namespace alpha1 {
    std::string get_error_message(DWORD code) {
        LPSTR buffer = nullptr;
        size_t size = FormatMessageA(MESSAGE_FLAGS, nullptr, code, LANG_ID, reinterpret_cast<LPSTR>(&buffer), 0, nullptr);

        std::string error_message = std::string(buffer, size);
        LocalFree(buffer);
        return error_message;
    }

    void display_error(DWORD code, const char *location, bool should_abort) {
        std::string message = get_error_message(code);

        std::stringstream message_stream;
        message_stream << "An error occurred in " << location << "\n"
                       << "Code: " << code << "\n"
                       << message;

        std::stringstream caption_stream;
        caption_stream << "alpha1 | ";

        if (should_abort) {
            message_stream << "\n\nWill abort.";
            caption_stream << "Fatal ";
        }

        caption_stream << "Error";

        (void)MessageBoxA(nullptr, message_stream.str().c_str(), caption_stream.str().c_str(), MB_OK | MB_ICONERROR);

        if (should_abort) {
            std::abort();
        }
    }
}
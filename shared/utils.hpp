#pragma once

#include <string>
#include <type_traits>
#include <windows.h>

#ifdef ALPHA1_DO_EXPORTS
#define ALPHA1_EXPORT __declspec(dllexport)
#else
#define ALPHA1_EXPORT
#endif

#define STR_WRAP(k) STR_WRAP_INNER(k)
#define STR_WRAP_INNER(k) #k

#define DISPLAY_ERROR(code) alpha1::display_error(code, __FILE__ ":" STRINGIFY(__LINE__), false)
#define DISPLAY_ERROR_ABORT(code) alpha1::display_error(code, __FILE_NAME__":" STR_WRAP(__LINE__), true)

#define DISPLAY_ABORT_UNLESS(expr)      \
{                                       \
    DWORD _err = expr;                  \
    if (_err)                           \
        DISPLAY_ERROR_ABORT(_err);      \
}

namespace alpha1 {
    [[nodiscard]] ALPHA1_EXPORT std::string get_error_message(DWORD code);
    ALPHA1_EXPORT void display_error(DWORD code, const char *location, bool should_abort);
}

#undef ALPHA1_EXPORT
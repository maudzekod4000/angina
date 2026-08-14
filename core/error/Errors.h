#ifndef PLATFORM_ERROR_H
#define PLATFORM_ERROR_H

#include <string>
#include <string_view>

#if defined(_MSC_VER)
    #define ANGINA_CURRENT_FUNCTION __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
    #define ANGINA_CURRENT_FUNCTION __PRETTY_FUNCTION__
#else
    #define ANGINA_CURRENT_FUNCTION __func__
#endif

namespace Core::Errors {

class ErrorCode {
public:
    ErrorCode() noexcept;
    explicit ErrorCode(int code, std::string&& msg, const char* functionName = "") noexcept;

    /// True, if there is an error.
    explicit operator bool() const noexcept {
        return code != 0;
    }

    operator std::string_view() const noexcept {
        return msg;
    }

    std::string_view function() const noexcept {
        return functionName;
    }
private:
    int code;
    std::string msg;
    std::string_view functionName;
};

}

#endif // !PLATFORM_ERROR_H

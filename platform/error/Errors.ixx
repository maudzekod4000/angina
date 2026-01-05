module;

#include <string>
#include <string_view>

export module errors;

namespace Angina::Errors {

export class ErrorCode {
public:
    ErrorCode() noexcept: code(0), msg("") {}
    explicit ErrorCode(int code, const std::string& msg) noexcept: code(code), msg(msg) {}

    /// True, if there is an error.
    explicit operator bool() const noexcept {
        return code != 0;
    }

    operator std::string_view() const noexcept {
        return msg;
    }
private:
    const int code;
    const std::string msg;
};

}

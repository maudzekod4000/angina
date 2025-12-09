module;

#include <string>

export module errors;

namespace Angina::Errors {

export class ErrorCode {
public:
    ErrorCode(): code(0), msg("") {}
    explicit ErrorCode(int code, const std::string& msg): code(code), msg(msg) {}

    const int code;
    const std::string msg;
};

}

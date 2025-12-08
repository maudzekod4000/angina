export module errors;

#include <string>

namespace Angina::Errors {

export class ErrorCode {
public:
    ErrorCode(): code(0), msg("") {}
    explicit ErrorCode(int code, const std::string& msg): code(code), msg(msg) {}

    const int code;
    const std::string msg;
};

}

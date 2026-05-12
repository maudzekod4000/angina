#include "Errors.h"

using namespace Core::Errors;

ErrorCode::ErrorCode() noexcept : code(0), msg(""), functionName("") {}

ErrorCode::ErrorCode(int code, const std::string& msg, const char* functionName) noexcept
	: code(code), msg(msg), functionName(functionName) {}

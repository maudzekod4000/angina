#include "Errors.h"

#include <utility>

using namespace Core::Errors;

ErrorCode::ErrorCode() noexcept : code(0), msg(""), functionName("") {}

ErrorCode::ErrorCode(int code, std::string&& msg, const char* functionName) noexcept
	: code(code), msg(std::move(msg)), functionName(functionName) {}

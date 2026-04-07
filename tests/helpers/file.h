#ifndef TESTS_HELPERS_FILE_H
#define TESTS_HELPERS_FILE_H

#include <vector>
#include <filesystem>

namespace Test::Helpers::File {
    std::vector<std::filesystem::path> loadFileNames(const std::filesystem::path& dir);
}

#endif // TESTS_HELPERS_FILE_H

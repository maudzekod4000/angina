#include "file.h"

std::vector<std::filesystem::path> Test::Helpers::File::loadFileNames(const std::filesystem::path& dir)
{
    std::vector<std::filesystem::path> res;

    if (std::filesystem::is_directory(dir) == false || std::filesystem::exists(dir) == false) {
        return res;
    }

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            res.push_back(entry.path());
        }
    }

    return res;
}

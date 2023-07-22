#include "FilePath.h"

// This should have the argv[0] passed here.
std::filesystem::path getExecutableLocation(std::string current_dir)
{
    return (std::filesystem::path(current_dir).parent_path());
}
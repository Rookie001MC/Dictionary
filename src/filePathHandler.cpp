#include "dictionary/filePathHandler.h"

std::string getExeDir(const char* exeDir)
{
    return (std::filesystem::path(exeDir).parent_path().string() + "/");
}
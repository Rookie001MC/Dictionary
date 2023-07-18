#ifndef FILEPATH_H
#define FILEPATH_H

#include <string>
#include <filesystem>

bool ifDictFileExist(std::string current_dir);
std::string getDictFileLocation(std::string current_dir);
std::filesystem::path getExecutableLocation(std::string current_dir);
#endif
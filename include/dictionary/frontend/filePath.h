#ifndef FILEPATH_H
#define FILEPATH_H

#include <string>
#include <filesystem>

std::filesystem::path getCurrentExeDir(const std::string current_dir);
#endif
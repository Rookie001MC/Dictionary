/**
 * @file dictionary/filePathHandler.cpp
 * @author Group7 - CS163 - 2022-2023
 * @brief Defining the function to get the path to the executable file
 * @version 1.0
 */
#include "dictionary/filePathHandler.h"

/**
 * @brief Get the current location of the executable file
 * 
 * @param exeDir The path to the executable file, usually is argv[0]
 * @return std::string The path to the executable file
 */
std::string getExeDir(const char *exeDir)
{
    return (std::filesystem::path(exeDir).parent_path().string() + "/");
}
#include "global.h"
std::filesystem::path getCurrentExeDir(const std::string current_dir)
{
    /**
     * @brief Gets the directory where the game is currently located
     * @param current_dir The current directory where the game is located
     * @return std::string of current game directory
     */
    return (std::filesystem::path(current_dir).parent_path());
}
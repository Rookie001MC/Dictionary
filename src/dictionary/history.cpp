/**
 * @file dictionary/history.cpp
 * @author Group7 - CS163 - 2022-2023
 * @brief Function definitions for the History class.
 * @version 1.0
 * @note This class also serves to store the user's favourite words.
 */
#include "dictionary/history.h"

/**
 * @brief Find the index of a key in the storage
 * 
 * @param key The key to be searched
 * @return int The index of the key in the storage
 */
int History::find(std::string key)
{
    for (int i = 0; i < storage.size(); ++i)
        if (storage.at(i) == key)
            return i;
    return -1;
}

/**
 * @brief Construct a new History::History object
 * 
 * @param path The path to the file containing the history
 * @param mode The mode of the History object, 0 for history (sorted by time), 1 for favorite (sorted by alphabet)
 */
History::History(std::string path, bool mode)
{
    std::ifstream fin(path);
    while (!fin.eof())
    {
        std::string tmp;
        std::getline(fin, tmp, '\n');
        if (!tmp.empty())
            storage.push_back(tmp);
    }
    fin.close();
    this->path = path;
    this->mode = mode;
    if (mode)
        std::sort(storage.begin(), storage.end());
}

/**
 * @brief Destroy the History::History object
 * @note This function is not used in the program, because, upon exiting the program, all of the preloaded Histories will be
 * destroyed. Adding another destructor for History will cause the program to cause a Segmentation Fault because it doesn't
 * know what History to clear. 
 */
History::~History()
{
    /* save(); */
}

/**
 * @brief Get the data of the History object
 * 
 * @return std::vector<std::string> The data of the History object
 */
std::vector<std::string> History::get()
{
    return storage;
}

/**
 * @brief Add a key to the History object
 * 
 * @param key The key to be added
 */
void History::add(std::string key)
{
    if (find(key) == -1)
        storage.push_back(key);
}

/**
 * @brief Remove a key from the History object
 * 
 * @param key The key to be removed
 */
void History::remove(std::string key)
{
    int index = find(key);
    if (index != -1)
        storage.erase(storage.begin() + index);
}

/**
 * @brief Save the History object to the file
 * 
 */
void History::save()
{
    if (mode)
        std::sort(storage.begin(), storage.end());
    std::ofstream fout(path);
    for (int i = 0; i < storage.size(); ++i)
        fout << storage.at(i) << std::endl;
    fout.close();
}

/**
 * @brief Clear the History object
 * 
 */
void History::clear()
{
    storage.clear();
}
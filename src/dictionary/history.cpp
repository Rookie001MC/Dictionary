#include "dictionary/history.h"

// mode 0: history - no alphabet indexing
// mode 1: favourite - alphabet indexing
int History::find(std::string key) {
    for (int i = 0; i < storage.size(); ++i)
        if (storage.at(i) == key)
            return i;
    return -1;
}

History::History(std::string path, bool mode = 0)
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
    if (mode) std::sort(storage.begin(), storage.end());
}

History::~History()
{
    save();
}

std::vector<std::string> History::get()
{
    return storage;
}

void History::add(std::string key)
{
    if (find(key) != -1)
        storage.push_back(key);
}

void History::remove(std::string key)
{
    int index = find(key);
    if (index != -1)
        storage.erase(storage.begin() + index);
}

void History::save()
{
    if (mode)
        std::sort(storage.begin(), storage.end());
    std::ofstream fout(path);
    for (int i = 0; i < storage.size(); ++i)
        fout << storage.at(i) << std::endl;
    fout.close();
}
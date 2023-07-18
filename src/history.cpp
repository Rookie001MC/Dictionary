#include "dictionary/history.h"
#include <algorithm>

// search for an index of a key word in the vector
int History::search(std::vector<std::string> vct, std::string key) {
    int mid = vct.size()/2, left = 0, right = vct.size() - 1;
    while (left < right) {
        if (vct.at(mid) == key)
            return mid;
        else if (key < vct.at(mid))
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

History::History(std::string path) {
    std::ifstream fin(path);
    while (!fin.eof()) {
        std::string tmp;
        std::getline(fin, tmp, '\n');
        storage.push_back(tmp);
    }
    fin.close();
    std::sort(storage.begin(), storage.end());
}

History::~History() {
    save();
}

std::vector<std::string> History::get() {
    return storage;
}

void History::add(std::string key) {
    if (search(storage, key) != -1)
        storage.push_back(key);
}

void History::remove(std::string key) {
    int index = search(storage, key);
    if (index != -1)
        storage.erase(storage.begin() + index);
}

void History::save() {
    std::sort(storage.begin(), storage.end());
    std::ofstream fout(path);
    for (int i = 0; i < storage.size(); ++i)
        fout << storage.at(i) << std::endl;
    fout.close();
}
#include "dictionary/build.h"
#include <iostream>

std::string nextKey;

void build(Dictionary &dict, Trie &trie) {
    std::string path;
    switch(dict.getDictionaryType()) {
        case 0:
            path = ENGENG;
            break;
        case 1:
            path = ENGVIE;
            break;
        case 2:
            path = VIEENG;
            break;
        case 3:
            path = EMOJI;
            break;
        case 4:
            path = SLANG;
            break;
    }
    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);
    if (!std::filesystem::exists(path + "history.txt")) {
        std::ofstream fout(path + "history.txt");
        fout.close();
    }
    if (!std::filesystem::exists(path + "favourite.txt")) {
        std::ofstream fout(path + "favourite.txt");
        fout.close();
    }
    if (std::filesystem::exists(path + "data.bin"))
        trie.deserialize(path + "data.bin");
    else
    {
        bool sign = false;
        while (!dict.eof()) {
            Word word = dict.getWord();
            if (nextKey == "" && !sign)     
                sign = true;
            else if (nextKey == "" && sign) // end of file
                break;
            trie.insert(word);
        }
        trie.serialize(path + "data.bin");
    }
}
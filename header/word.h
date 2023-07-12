#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>

class Definition {
    private:
        std::string def;
        std::vector<std::string> usage;
    public:
        void setDef(std::string key);
        void setUsage(std::string key);
};


class Word {
    private:
        std::string key;
        std::string type;
        std::vector<Definition> defs;
    public:
        Word(std::string key);
        ~Word();
        void setKey(int k);
        void setType(std::string type);
        void editDef(int index, std::string newDef);
        void removeDef(int index);
        void addDef(std::string newDef);
};

class Dictionary {
    private:
        std::ifstream fin;
        int dictType; // 0: eng-eng, 1: eng-vie, 2: vie-eng, 3: emoji, 4: slang
        Word getWordEngEng();
        Word getWordEngVie();
        Word getWordVieEng();
        Word getWordEmoji();
        Word getWordSlang();
    public:
        Dictionary(std::string path, int dictType);
        ~Dictionary();
        Word getWord();
};

#endif
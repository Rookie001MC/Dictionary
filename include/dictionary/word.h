#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>

class Word {
    private:
        std::string key;
        std::string type;
        std::vector<std::string> definitions;
    public:        
        Word(std::string key, std::vector<std::string> definition, std::string type);
        void setKey(std::string key);
        void setType(std::string type);
        void setDefinition(std::string newDefinition,int definitionIndex);
};

class Dictionary {
    private:
        std::ifstream fin;
        int dictType; // 0: eng-eng, 1: eng-vie, 2: vie-eng, 3: emoji, 4: slang
        Word getWordEngEng();
        Word getWordEngVie();
        Word getWordVieEng();
        Word getWordKaomoji(std::ifstream &fin);
        Word getWordSlang();
        Word getWordEmoji(std::ifstream &fin);
    public:
        Dictionary(std::string path, int dictType);
        ~Dictionary();
        Word getWord();
};

#endif
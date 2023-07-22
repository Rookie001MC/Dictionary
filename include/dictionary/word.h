#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <utility>
#include <fstream>

class Word {
    private:
        std::wstring key;
        std::wstring type;
        std::vector<std::wstring> definitions;
    public:        
        Word(std::wstring key , std::wstring definition, std::wstring type);
        std::wstring getKey();
        std::wstring getType();
        std::wstring getDefinition(int index);
        int getDefinitionCount();
        void setKey(std::wstring key);
        void setType(std::wstring type);
        void setDefinition(std::wstring definition, int index);
};

class Dictionary {
    private:
        std::wifstream fin;
        int dictType; // 0: eng-eng, 1: eng-vie, 2: vie-eng, 3: emoji, 4: slang
        Word getWordEngEng();
        Word getWordEngVie();
        Word getWordVieEng();
        Word getWordKaomoji(std::ifstream &fin);
        Word getWordSlang();
        Word getWordEmoji(std::ifstream &fin, int index);
    public:
        Dictionary(std::string path, int dictType);
        ~Dictionary();
        Word getWord();
};

#endif
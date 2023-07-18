#include "dictionary/word.h"

// define Word
Word::Word(std::string key, std::vector<std::string> definitions, std::string type = "") {
    this->key = key;
    this->type = type;
    this->definitions = definitions;
}

void Word::setKey(std::string key) {
    this->key = key;
}

void Word::setType(std::string type) {
    this->type = type;
}

void Word::setDefinition(std::string newDefinition, int definitionIndex = 0) {
    this->definitions[definitionIndex] = newDefinition;
}

// define Dictionary
Dictionary::Dictionary(std::string path, int dictType) {
    fin.open(path);
    this->dictType = dictType;
}

Dictionary::~Dictionary() {
    fin.close();
}

Word Dictionary::getWord() {
    switch(dictType) {
        case 0:
            return getWordEngEng();
        case 1:
            return getWordEngVie();
        case 2:
            return getWordVieEng();
        case 3:
            return getWordKaomoji(fin);
        case 4:
            return getWordSlang();
        case 5:
            return getWordEmoji();
    }   
}
#include "dictionary/word.h"

// define Word
Word::Word(std::string key, std::string definition , std::string type = "") {
    this->key = key;
    this->type = type;
    this->definition = definition;
}

void Word::setKey(std::string key) {
    this->key = key;
}

void Word::setType(std::string type) {
    this->type = type;
}

void Word::setDefinition(std::string definition) {
    this->definition = definition;
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
            return getWordEmoji();
        case 4:
            return getWordSlang();
    }
}
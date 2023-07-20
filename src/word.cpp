#include "dictionary/word.h"

// define Word
Word::Word(std::wstring key = L"", std::wstring definition = L"" , std::wstring type = L"") {
    this->key = key;
    this->type = type;
    definitions.push_back(definition);
}

std::wstring Word::getKey() {
    return key;
}
std::wstring Word::getType() {
    return type;
}
std::wstring Word::getDefinition(int index) {
    return definitions.at(index);
}

int Word::getDefinitionCount() {
    return definitions.size();
}

void Word::setKey(std::wstring key) {
    this->key = key;
}

void Word::setType(std::wstring type) {
    this->type = type;
}

void Word::setDefinition(std::wstring definition, int index) {
    definitions.at(index) = definition;
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

Word Dictionary::getWordVieEng() {
    std::wstring key, definition, type, tmp;
    std::getline(fin, key, L'\n');
    key = key.substr(1);
    std::getline(fin, tmp, L'\n');
    while (!tmp.empty()) {
        if (tmp.at(0) == L'*')
            type += (tmp.substr(1) + L'/');
        if (tmp.at(0) == L'=') {
            int pos = tmp.find(L'+');
            definition += (L"Example: " + tmp.substr(1, pos - 1) + L": " + tmp.substr(pos + 1) + L'\n');
        }
        definition += (tmp + L'\n');
    }
    type = type.substr(0, type.size() - 1);
    Word word(key, definition, type);
    return word;
}
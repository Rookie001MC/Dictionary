#include "dictionary/word.h"
#include <sstream>
#include <string>

// define Word
Word::Word(std::wstring key = L"", std::wstring definition = L"" , std::wstring type = L"") {
    this->key = key;
    this->type = type;
    definitions.push_back(definition);

}

std::vector<std::wstring> Word::getDefinitions() {
    return definitions;
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
            return getWordKaomoji(fin);
        case 4:
            return getWordSlang();
        case 5:
            // TODO: Fix the code so that it supports the JSON array in the emoji.dict file. 
            return getWordEmoji(fin, 0);
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

std::wstring extractDefinition(const std::wstring& line, bool &isEndOfDefinition)
{
    // get the whole line except when meet the '[' - meaning that the definition is over
    std::wstring definition;
    if (line.find('[') == std::wstring::npos)    // this character doesn't exist
    {
        int start = line.find_first_not_of(' ');
        definition = line.substr(start);
    }
    else
    {
        // find the position that is not a space 
        // then find the last position (the position appearing '[')
        // then get the substring from the first position to the last position
        int firstPos = line.find_first_not_of(' ');
        int lastPos = line.find('[');
        isEndOfDefinition = true;
        definition = line.substr(firstPos, lastPos - firstPos);
    }
    definition.append(L"\n");
    return definition;
}

std::wstring extractWordType(const std::wstring& line)
{
    std::wstring wordType;
    std::wistringstream iss(line);
    iss >> std::skipws >> wordType;
    return wordType;
}

Word Dictionary::getWordEngEng()
{
    std::wifstream fin;
    fin.open("engeng.dict");
    bool isEndOfDefinition = false;
    bool flag = true;
    Word word(L"", L"", L"");
    std::wstring line;
    int curDef = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == ' ') // if the line starts with a space, it is a definition
        {
            if (line[5] >= 'a' && line[5] <= 'z')   // the sign of wordType
            {
                std::wstring wordType = extractWordType(line);
                if (word.getType().length() == 0)    // not have a wordType yet
                    word.setType(wordType);
                
                else    
                {
                    std::wstring tmp = word.getType();
                    tmp.append(L"/" + wordType);
                    word.setType(tmp);
                }
                if (isEndOfDefinition)
                    word.getDefinitions().push_back(L"");   // if this sign is true, it means we are in a new definition
                isEndOfDefinition = false;
            }
            else if (line[5] >= '0' && line[5] <= '9')  // start of a new definition
            {
                word.getDefinitions().push_back(L"");   // create a new slot for the new definition
                isEndOfDefinition = false;
                flag = true;                            // reset the flag
            }    
            if (!isEndOfDefinition)
            {
                std::wstring tmpDef = word.getDefinition(curDef); 
                tmpDef.append(extractDefinition(line, isEndOfDefinition));
                word.setDefinition(tmpDef, curDef);
            }
            else
            {
                if (flag)
                {
                    curDef++;
                    flag = false;
                }    
            }
        }
        else // if the line starts with a letter, it is a word
        {
            if (word.getKey() == L"")   // doesn't have anything
                word.setKey(line);
            else
                break;
        }
    }
    fin.close();
    return word;
}
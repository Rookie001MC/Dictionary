#include "dictionary/word.h"
#include <sstream>
#include <string>
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

std::string Word::getKey()
{
    return this->key;
}

std::string Word::getDefinition()
{
    return this->definition;
}

std::string Word::getType()
{
    return this->type;
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
std::string extractDefinition(const std::string& line, bool &isEndOfDefinition)
{
    // get the whole line except when meet the '[' - meaning that the definition is over
    std::string definition;
    if (line.find('[') == std::string::npos)    // this character doesn't exist
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
    definition.append("\n");
    return definition;
}

std::string extractWordType(const std::string& line)
{
    std::string wordType;
    std::istringstream iss(line);
    iss >> std::skipws >> wordType;
    return wordType;
}

Word Dictionary::getWordEngEng()
{
    std::ifstream fin;
    fin.open("engeng.dict");
    bool isEndOfDefinition = false;
    Word word("", "", "");
    std::string line;
    while (getline(fin, line))
    {
        if (line[0] == ' ') // if the line starts with a space, it is a definition
        {
            if (line[5] >= 'a' && line[5] <= 'z')   // the sign of wordType
            {
                std::string wordType = extractWordType(line);
                if (word.getType().length() == 0)    // not have a wordType yet
                    word.setType(wordType);
                
                else    
                {
                    std::string tmp = word.getType();
                    tmp.append("/" + wordType);
                    word.setType(tmp);
                }
                isEndOfDefinition = false;
            }
            else if (line[5] >= '0' && line[5] <= '9')  // start of a new definition
                isEndOfDefinition = false;
            if (!isEndOfDefinition)
            {
                std::string tmpDef = word.getDefinition();
                tmpDef.append(extractDefinition(line, isEndOfDefinition));
                word.setDefinition(tmpDef);
            }
        }
        else // if the line starts with a letter, it is a word
        {
            if (word.getKey() == "")   // doesn't have anything
                word.setKey(line);
            else
                break;
        }
    }
    fin.close();
    return word;
}

#include "dictionary/word.h"
using json = nlohmann::json;

extern std::string nextKey;

// define Word
Word::Word() {
    key = "";
    type = "";
}

Word::Word(std::string key, std::string definition = "" , std::string type = "") {
    this->key = key;
    this->type = type;
    if (!definition.empty())
        definitions.push_back(definition);
}

std::vector<std::string> Word::getDefinitions() {
    return definitions;
}

std::vector<std::string>& Word::accessDefinitions() {
    return definitions;
}

std::string Word::getKey() {
    return key;
}
std::string Word::getType() {
    return type;
}
std::string Word::getDefinition(int index) {
    if (definitions.size() <= index)
        return "";
    return definitions.at(index);
}

int Word::getDefinitionCount() {
    return definitions.size();
}

void Word::setKey(std::string key) {
    this->key = key;
}

void Word::setType(std::string type) {
    this->type = type;
}

void Word::setDefinition(std::string definition, int index) {
    definitions.at(index) = definition;
}

void Word::addDefinition(std::string definition) {
    this->definitions.push_back(definition);
}

// define Dictionary
Dictionary::Dictionary(std::string path, int dictType) {
    fin.open(path);
    this->dictType = dictType;
}

Dictionary::~Dictionary() {
    fin.close();
}

int Dictionary::getDictionaryType() {
    return dictType;
}

bool Dictionary::eof() {
    return fin.eof();
}

Word Dictionary::getWord() {
    switch(dictType) {
        case 0:
            return getWordEngEng();
        // case 1:
        //     return getWordEngVie();
        case 2:
            return getWordVieEng();
        // case 3:
        //     return getWordKaomoji(fin);
        // case 4:
        //     return getWordSlang();
        // case 5:
        //     // TODO: Fix the code so that it supports the JSON array in the emoji.dict file. 
        //     return getWordEmoji(fin, 0);
    }
    return Word();
}

Word Dictionary::getWordVieEng() {
    std::string key, type, tmp;
    std::getline(fin, key, '\n');
    key = key.substr(1);
    Word word(key);
    std::getline(fin, tmp, '\n');
    while (!tmp.empty()) {
        if (tmp.at(0) == '*')
            type += (tmp.substr(1) + '/');
        else if (tmp.at(0) == '=') {
            int pos = tmp.find('+');
            word.addDefinition("Example: " + tmp.substr(1, pos - 1) + ": " + tmp.substr(pos + 1) + '\n');
        }
        else
            word.addDefinition(tmp.substr(1) + '\n');
        
        std::getline(fin, tmp, '\n');
    }
    type = type.substr(0, type.size() - 1);
    word.setType(type.substr(0, type.size() - 1));
    return word;
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
    definition.append(" ");
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
    bool isEndOfDefinition = false;
    bool start = false;
    Word word(nextKey, "", "");
    std::string line;
    int curDef = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == ' ') // if the line starts with a space, it is a definition
        {
            if (line[5] >= 'a' && line[5] <= 'z')   // the sign of wordType
            {
                if (nextKey != "")
                    start = true;
                if (!start)
                    isEndOfDefinition = true;
                std::string wordType = extractWordType(line);
                if (word.getType().length() == 0)    // not have a wordType yet
                    word.setType(wordType);
                
                else    
                {
                    std::string tmp = word.getType();
                    tmp.append("/" + wordType);
                    word.setType(tmp);
                }
                if (isEndOfDefinition)
                    word.getDefinitions().push_back("");   // if this sign is true, it means we are in a new definition
                isEndOfDefinition = false;
                if (!start)
                    curDef++;
                else
                    start = false;
            }
            else if (line[5] >= '0' && line[5] <= '9')  // start of a new definition
            {
                word.getDefinitions().push_back("");   // create a new slot for the new definition
                isEndOfDefinition = false;
                curDef++;
            }    
            if (!isEndOfDefinition)
            {   
                if (word.getDefinitionCount() <= curDef)
                    word.addDefinition("");
                std::string tmpDef = word.getDefinition(curDef); 
                tmpDef.append(extractDefinition(line, isEndOfDefinition));
                word.setDefinition(tmpDef, curDef);
            }
        }
        else // if the line starts with a letter, it is a word
        {
            if (word.getKey() == "")   // doesn't have anything
            {
                word.setKey(line);
                start = true;
            }
            else
            {
                nextKey = line;
                break;
            }
        }
    }
    return word;
}

Word Dictionary::getWordEngVie() {
    fin.open("../../data/engvie.dict");
    std::string key, type, tmp;
    std::getline(fin, key, '\n');
    key = key.substr(1);
    Word word(key, "", "");
    std::getline(fin, tmp, '\n');
    while (!tmp.empty()) {
        if (tmp.at(0) == '*')
            type += (tmp.substr(1) + '/');
        else if (tmp.at(0) == '=') {
            int pos = tmp.find('+');
            word.addDefinition("Example: " + tmp.substr(1, pos - 1) + ": " + tmp.substr(pos + 1) + '\n');
        }
        else
            word.addDefinition(tmp.substr(1) + '\n');
        
        std::getline(fin, tmp, '\n');
    }
    type = type.substr(0, type.size() - 1);
    word.setType(type.substr(0, type.size() - 1));
    return word;
}


 /*
    Note:
        Khác biệt giữa getWordEmoji và getWordKaomoji là do file emoji.dict là mảng JSON thay vì object JSON như file
        kaomoji.dict, nên cần truyền thêm index vào hàm getWordEmoji để lấy được từng phần tử trong mảng.
 */
Word Dictionary::getWordEmoji(int index)
{

    Word tmpEmoji;
    json j;
    fin >> j;

    auto currentEmoji = j.begin() + index;
    std::string key = currentEmoji->at("emoji").get<std::string>();
    std::string type = currentEmoji->at("category").get<std::string>();
    tmpEmoji.setKey(key);
    tmpEmoji.setType(type);

    // True definition should be the description of the emoji
    std::string definition = currentEmoji->at("description").get<std::string>();
    tmpEmoji.addDefinition(definition);

    return tmpEmoji;
 
}

Word Dictionary::getWordKaomoji()
{

    Word tmpKaomoji;
   json j;
   fin >> j;

   std::string key = j.begin().key();
   std::string type = "kaomoji";
   std::vector<std::string> definitions = j[key]["original_tags"].get<std::vector<std::string>> ();
   std::vector<std::string> new_tags = j[key]["new_tags"].get<std::vector<std::string>> ();

    tmpKaomoji.setKey(key);
    tmpKaomoji.setType(type);

    for (auto definition : definitions)
    {
        tmpKaomoji.addDefinition(definition);
    }

    return tmpKaomoji;
}
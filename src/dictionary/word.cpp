#include "dictionary/word.h"

extern std::string nextKey;

// define Word
Word::Word()
{
    key  = "";
    type = "";
}

Word::Word(std::string key, std::string type, std::string definition)
{
    this->key  = key;
    this->type = type;
    if (!definition.empty())
        definitions.push_back(definition);
}

std::vector<std::string> Word::getDefinitions()
{
    return definitions;
}

std::string Word::getKey()
{
    return key;
}
std::string Word::getType()
{
    return type;
}
std::string Word::getDefinition(int index)
{
    if (definitions.size() <= index)
        return "";
    return definitions.at(index);
}

int Word::getDefinitionCount()
{
    return definitions.size();
}

void Word::setKey(std::string key)
{
    this->key = key;
}

void Word::setType(std::string type)
{
    this->type = type;
}

void Word::setDefinition(std::string definition, int index)
{
    definitions.at(index) = definition;
}

void Word::addDefinition(std::string definition)
{
    for (int i = 0; i < getDefinitionCount(); ++i)
        if (getDefinition(i) == definition)
            return;
    this->definitions.push_back(definition);
}

void Word::removeDefinition(int index) {
    if (index < definitions.size())
        definitions.erase(definitions.begin() + index);
}

// define Dictionary
Dictionary::Dictionary(std::string path, int dictType)
{
    fin.open(path);
    this->dictType = dictType;
}

Dictionary::~Dictionary()
{
    fin.close();
}

int Dictionary::getDictionaryType()
{
    return dictType;
}

bool Dictionary::eof()
{
    return fin.eof();
}

Word Dictionary::getWord()
{
    switch (dictType)
    {
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
    return Word();
}

std::string extractDefinition(const std::string &line, bool &isEndOfDefinition)
{
    // get the whole line except when meet the '[' - meaning that the definition is over
    // Cases when the definition is over
    // 1. the line contains '[' -> the sign of synonym at the end of the definition
    // 2. the appearance of "; "" -> start of the example -> also at the end of the definition
    std::string definition;
    if (line.find('[') == std::string::npos) // this character doesn't exist
    {
        int start = line.find_first_not_of(' ');
        if (line.find("; \"") != std::string::npos)
        {
            int end           = line.find("; \"") - 1;
            isEndOfDefinition = true;
            definition        = line.substr(start, end - start + 1);
        }
        else
            definition = line.substr(start);
    }
    else
    {
        int firstPos = line.find_first_not_of(' ');
        int lastPos  = 0;
        if (line.find("; \"") != std::string::npos)
            lastPos = line.find("; \"");
        else
            lastPos = line.find('[');
        isEndOfDefinition = true;
        definition        = line.substr(firstPos, lastPos - firstPos);
    }
    definition.append(" ");
    return definition;
}

std::string extractWordType(const std::string &line)
{
    std::string wordType;
    std::istringstream iss(line);
    iss >> std::skipws >> wordType;
    return wordType;
}

Word Dictionary::getWordEngEng()
{
    bool isEndOfDefinition = false;
    bool start             = false;
    Word word(nextKey, "", "");
    std::string line;
    int curDef = 0;
    while (std::getline(fin, line))
    {
        if (line[0] == ' ') // if the line starts with a space, it is a definition
        {
            if (line[5] >= 'a' && line[5] <= 'z') // the sign of wordType
            {
                if (nextKey != "")
                    start = true;
                if (!start)
                    isEndOfDefinition = true;
                std::string wordType = extractWordType(line);
                if (word.getType().length() == 0) // not have a wordType yet
                    word.setType(wordType);

                else
                {
                    std::string tmp = word.getType();
                    tmp.append("/" + wordType);
                    word.setType(tmp);
                }
                if (isEndOfDefinition)
                {
                    word.addDefinition("");
                    curDef++;
                }
                isEndOfDefinition = false;
            }
            else if (line[5] >= '0' && line[5] <= '9') // start of a new definition
            {
                word.addDefinition("");
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
            if (word.getKey() == "") // doesn't have anything
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

// at the end of each definition has a '\n' character.
// it can be erased easily from the code below, but will somehow cause bug !?
Word Dictionary::getWordEngVie()
{
    std::string key = "", type, tmp;
    std::getline(fin, key, '\n');
    int posStop = key.find('/');
    key         = key.substr(1, posStop - 2);
    Word word(key, "", "");
    std::getline(fin, tmp, '\n');
    while (!tmp.empty())
    {
        if (tmp.at(0) == '*')
            type += (tmp.substr(1) + '/');
        else if (tmp.at(0) == '=')
        {
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

// words that don't have type will have "na" as type
Word Dictionary::getWordVieEng()
{
    std::string key, type, tmp;
    std::getline(fin, key, '\n');
    key = key.substr(1);
    Word word(key);
    std::getline(fin, tmp, '\n');
    while (!tmp.empty())
    {
        if (tmp.at(0) == '*')
            type += (tmp.substr(1) + '/');
        else if (tmp.at(0) == '=')
        {
            int pos = tmp.find('+');
            word.addDefinition("Example: " + tmp.substr(1, pos - 1) + ": " + tmp.substr(pos + 1));
        }
        else
            word.addDefinition(tmp.substr(1));

        std::getline(fin, tmp, '\n');
    }
    if (type.empty())
        type = "na";
    type = type.substr(0, type.size() - 1);
    word.setType(type);
    return word;
}

Word Dictionary::getWordEmoji()
{
    std::string key, type = "slang", definition;
    getline(fin, key, '\t');
    getline(fin, definition, '\n');
    Word word(key, type, definition);
    return word;
}

Word Dictionary::getWordSlang()
{
    std::string key, type = "slang", definition;
    getline(fin, key, '\t');
    getline(fin, definition, '\n');
    Word word(key, type, definition);
    return word;
}
#ifndef BACKEND_WORD_H
#define BACKEND_WORD_H

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
class Word
{
  private:
    std::string key;
    std::string type;
    std::vector<std::string> definitions;

  public:
    Word();
    Word(std::string key, std::string type = "", std::string definition = "");
    std::string getKey();
    std::string getType();
    std::string getDefinition(int index);
    std::vector<std::string> getDefinitions();
    int getDefinitionCount();
    void setKey(std::string key);
    void setType(std::string type);
    void setDefinition(std::string definition, int index);
    void addDefinition(std::string definition);
    void removeDefinition(int index);
    void editDefinition(int index, std::string edit);
};

class Dictionary
{
  private:
    std::ifstream fin;
    std::string path;
    int dictType; // 0: eng-eng, 1: eng-vie, 2: vie-eng, 3: emoji, 4: slang
    Word getWordEngEng();
    Word getWordEngVie();
    Word getWordVieEng();
    Word getWordSlang();
    Word getWordEmoji();

  public:
    Dictionary(std::string path, int dictType);
    ~Dictionary();
    Word getWord();
    int getDictionaryType();
    bool eof();
    void reset();
};

#endif
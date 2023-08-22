#ifndef BACKEND_SEARCH_DEF_H
#define BACKEND_SEARCH_DEF_H

#include "trie.h"
#include "word.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

class RelevantWord
{
  private:
    Dictionary *dictionary;
    std::string keywordPath;
    std::string filePath;
    Word word;
    double relevance;

  public:
    RelevantWord();
    RelevantWord(Word word, double relevance);
    void setDictionary(Dictionary *dict);
    void setPath();
    std::string getKeyWordPath();
    std::string getFilePath();
    std::vector<RelevantWord> searchDefinition(std::string definitionFromUser, Trie &trie);
    double getRelevance();
    Word getWord();
};

// support functions
std::string preprocessText(std::string text);
void wordHashing(std::string line, std::unordered_set<std::string> &wordCounts);
double calculateRelevance(std::string userInput, std::unordered_set<std::string> &wordCounts);

#endif
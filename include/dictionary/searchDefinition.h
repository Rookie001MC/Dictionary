#ifndef BACKEND_SEARCH_DEF_H
#define BACKEND_SEARCH_DEF_H

#include "word.h"
#include "trie.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

class RelevantWord
{
  private:
    Word word;
    double relevance;
  public:
    RelevantWord();
    RelevantWord(Word word, double relevance);
    std::vector<RelevantWord> searchDefinition(std::string definitionFromUser, Trie &trie);
    double getRelevance();
    Word getWord();
};

// support functions
bool comparingRelevance(RelevantWord a, RelevantWord b);
std::string preprocessText(std::string text);
void wordHashing(std::string line, std::unordered_set<std::string> &wordCounts);
double calculateRelevance(std::string userInput, std::unordered_set<std::string> &wordCounts);


#endif
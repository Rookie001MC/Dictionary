#ifndef BACKEND_SEARCH_DEF_H
#define BACKEND_SEARCH_DEF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <unordered_set>
#include "word.h"

// Search exact definition that user enters
// In the future, max-heap will be used to show the most relevant definition (50% match and more will be shown in
// priority)
// In the future, max-heap will be used to show the most relevant definition (50% match and more will be shown in priority)

struct RelevantWord
{
    Word word;
    double relevance;
};

std::string preprocessText(std::string text);
bool comparingRelevance(RelevantWord &a, RelevantWord &b);
void wordHashing(std::string line, std::unordered_set<std::string> &wordCounts);
void lineHash(std::vector<std::string> &lines);
double calculateRelevance(std::string userInput, std::unordered_set<std::string> &wordCounts);
std::vector<RelevantWord> searchDefinition(std::string definitionFromUser);

#endif
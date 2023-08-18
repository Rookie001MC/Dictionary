#include "dictionary/searchDefinition.h"

RelevantWord::RelevantWord(Word word, double relevance)
{
    this->word      = word;
    this->relevance = relevance;
}

double RelevantWord::getRelevance()
{
    return this->relevance;
}

std::string preprocessText(std::string text)
{
    std::regex pattern("[[:punct:]]");
    text = std::regex_replace(text, pattern, "");
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

double calculateRelevance(std::string userInput, std::unordered_set<std::string> &wordCounts)
{
    int matchWord = 0;
    int totalInputWords = 0;
    std::istringstream iss(userInput);
    std::string word;
    while (iss >> word)
    {
        ++totalInputWords;
        auto it = wordCounts.find(word);
        if (it != wordCounts.end())
            matchWord++;
    }
    double percent = double(matchWord) / double(totalInputWords);
    return percent;
}

void wordHashing(std::string line, std::unordered_set<std::string> &wordCounts)
{
    std::istringstream iss(line);
    std::string word;
    while (iss >> word)
    {
        auto it = wordCounts.find(word);
        if (it == wordCounts.end())
            wordCounts.emplace(word);
    }
}
void lineHash(std::vector<std::string> &lines)
{
    std::ifstream read("../data/engeng_processed.txt");
    std::string line;
    while (std::getline(read, line))
    {
        lines.push_back(line);
    }
}

bool comparingRelevance(RelevantWord a, RelevantWord b)
{
    return a.getRelevance() > b.getRelevance();
}

std::vector<RelevantWord> RelevantWord::searchDefinition(std::string definitionFromUser, Trie &trie)
{
    // definitionFromUser = preprocessText(definitionFromUser);
    
    std::ifstream read;
    std::ifstream file;
    read.open("../data/engengRandom.txt"); 
    std::string line;
    std::string processed;
    std::string def = "";
    std::vector<RelevantWord> words;
    int wordLimit = 20;

    while (std::getline(read, line) && std::getline(file, processed))
    {
        Word word;
        std::unordered_set<std::string> wordCounts;
        wordHashing(processed, wordCounts);
        double percent = calculateRelevance(definitionFromUser, wordCounts);

        if (percent >= 0.5)
        {
            std::string keyWord = line.substr(0, line.find('#') - 1); // get the word
            if (trie.search(keyWord, word))
            {
                RelevantWord relWord{word, percent};
                words.push_back(relWord);
            }
            // int startType    = line.find('#') + 1;
            // int endType      = line.find_first_of('@') - 2;
            // std::string type = line.substr(startType, endType - startType + 1);

            // word.setKey(keyWord);
            // word.setType(type);

            // int index = endType + 2;
            // while (index < line.length())
            // {
            //     int nextAtPos = line.find('@', index + 1);
            //     if (nextAtPos == std::string::npos)
            //         break;
            //     def   = line.substr(index + 1, nextAtPos - index - 2);
            //     index = nextAtPos;
            //     word.addDefinition(def);
            // }
        }
        if (words.size() == wordLimit)
            break;
    }
    // std::sort(words.begin(), words.end(), comparingRelevance);
    return words;
}

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
    file.open("../data/engeng_processed.txt"); 
    read.open("../data/engengKeyWord.txt");
    
    std::string keyWord;
    std::string processed;
    std::vector<RelevantWord> words;
    int wordLimit = 20;

    while (std::getline(read, keyWord) && std::getline(file, processed))
    {
        Word word;
        std::unordered_set<std::string> wordCounts;
        wordHashing(processed, wordCounts);
        double percent = calculateRelevance(definitionFromUser, wordCounts);

        if (percent >= 0.5)
        {
            if (trie.search(keyWord, word))
            {
                RelevantWord relWord{word, percent};
                words.push_back(relWord);
            }
        }
        if (words.size() == wordLimit)
            break;
    }
    // std::sort(words.begin(), words.end(), comparingRelevance);
    return words;
}

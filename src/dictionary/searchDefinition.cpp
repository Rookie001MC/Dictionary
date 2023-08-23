#include "dictionary/searchDefinition.h"

RelevantWord::RelevantWord()
{
    this->relevance = 0;
}

RelevantWord::RelevantWord(Word word, double relevance)
{
    this->word      = word;
    this->relevance = relevance;
}

double RelevantWord::getRelevance()
{
    return this->relevance;
}

Word RelevantWord::getWord()
{
    return this->word;
}

void RelevantWord::setDictionary(Dictionary *dict)
{
    this->dictionary = dict;
}

void RelevantWord::setPath()
{
    int mode = this->dictionary->getDictionaryType();
    switch(mode)
    {
        case 0:
            this->keywordPath = "../data/engengKeyWord.txt";
            this->filePath    = "../data/engeng_processed.txt";
            break;
        case 1:
            this->keywordPath = "../data/engvieKeyWord.txt";
            this->filePath    = "../data/engvie_processed.txt";
            break;
        case 2:
            this->keywordPath = "../data/vieengKeyWord.txt";
            this->filePath    = "../data/vieeng_processed.txt";
            break;
        case 3:
            this->keywordPath = "../data/emojiKeyWord.txt";
            this->filePath    = "../data/emoji_processed.txt";
            break;
        case 4:
            this->keywordPath = "../data/slangKeyWord.txt";
            this->filePath    = "../data/slang_processed.txt";
            break;
    }
}

std::string RelevantWord::getKeyWordPath()
{
    return this->keywordPath;
}

std::string RelevantWord::getFilePath()
{
    return this->filePath;
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
    int matchWord       = 0;
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

std::vector<RelevantWord> RelevantWord::searchDefinition(std::string definitionFromUser, Trie &trie)
{
    // definitionFromUser = preprocessText(definitionFromUser);
    std::transform(definitionFromUser.begin(), definitionFromUser.end(), definitionFromUser.begin(), ::tolower);
    std::ifstream read;
    std::ifstream file;
    file.open(getFilePath());
    read.open(getKeyWordPath());

    std::string keyWord;
    std::string processed;
    std::vector<RelevantWord> words;
    int wordLimit = 10;

    while (std::getline(read, keyWord) && std::getline(file, processed))
    {
        Word word;
        std::unordered_set<std::string> wordCounts;
        wordHashing(processed, wordCounts);
        double percent = calculateRelevance(definitionFromUser, wordCounts);

        if (percent >= 0.3)
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
    return words;
}

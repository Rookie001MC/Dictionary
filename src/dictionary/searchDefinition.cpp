/**
 * @file dictionary/searchDefinition.cpp
 * @author Group7 - CS163 - 2022-2023
 * @brief Function definitions for the Random class.
 * @version 1.0
 */
#include "dictionary/searchDefinition.h"

/**
 * @brief Construct a new RelevantWord::RelevantWord object
 * 
 */
RelevantWord::RelevantWord()
{
    this->relevance = 0;
}

/**
 * @brief Construct a new RelevantWord::RelevantWord object, with the Word object and the relevance index
 * 
 * @param word The Word object
 * @param relevance The relevance index
 */
RelevantWord::RelevantWord(Word word, double relevance)
{
    this->word      = word;
    this->relevance = relevance;
}

/**
 * @brief Get the relevance index
 * 
 * @return double The relevance index
 */
double RelevantWord::getRelevance()
{
    return this->relevance;
}

/**
 * @brief Get the key of the Word object
 * 
 * @return Word the key of the Word object
 */
Word RelevantWord::getWord()
{
    return this->word;
}

/**
 * @brief Set the dictionary to be used
 * 
 * @param dict The Dictionary object to be used
 */
void RelevantWord::setDictionary(Dictionary *dict)
{
    this->dictionary = dict;
}

/**
 * @brief Set the path of the keyword file and the processed file
 * 
 */
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

/**
 * @brief Get the path of the keyword file
 * 
 * @return std::string The path of the keyword file
 */
std::string RelevantWord::getKeyWordPath()
{
    return this->keywordPath;
}

/**
 * @brief Get the path of the processed file
 * 
 * @return std::string 
 */
std::string RelevantWord::getFilePath()
{
    return this->filePath;
}

/**
 * @brief Preprocess the text by transforming all characters to lowercase and removing all punctuations
 * 
 * @param text The text to be preprocessed
 * @return std::string The preprocessed text 
 */
std::string preprocessText(std::string text)
{
    std::regex pattern("[[:punct:]]");
    text = std::regex_replace(text, pattern, "");
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

/**
 * @brief Calculate the relevance index of the input text
 * 
 * @param userInput The input text
 * @param wordCounts The set of words in the definition
 * @return double The relevance index
 */
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

/**
 * @brief Hash the words in the definition
 * 
 * @param line The definition
 * @param wordCounts The set of words in the definition
 */
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

/**
 * @brief Search the definition of the input text
 * 
 * @param definitionFromUser The input text
 * @param trie The Trie object
 * @return std::vector<RelevantWord> The words that have the relevance index greater than 0.3
 */
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

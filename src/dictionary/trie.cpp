/**
 * @file dictionary/trie.cpp
 * @author Group7 - CS163 - 2022-2023
 * @brief Function definitions for the Trie class.
 * @version 1.0
 */
#include "dictionary/trie.h"
#include <algorithm>
#include <ctype.h>

/**
 * @brief Construct a new Trie::Trie object by calling init()
 *
 */
Trie::Trie()
{
    init();
}

/**
 * @brief Initialize the Trie object by creating a new TrieNode object and set its endOfWord to false
 *
 */
void Trie::init()
{
    this->root      = new TrieNode;
    root->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        root->children[i] = nullptr;
}

/**
 * @brief Destroy the Trie::Trie object
 * @note This function is not used in the program, because, upon exiting the program, all of the preloaded Tries will be
 * destroyed. Adding another destructor for Trie will cause the program to cause a Segmentation Fault because it doesn't
 * know what Trie to clear.
 */
Trie::~Trie()
{
    /*      clear();*/
}
/**
 * @brief Create a Node object
 *
 * @return TrieNode*
 */
TrieNode *Trie::createNode()
{
    TrieNode *node  = new TrieNode;
    node->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        node->children[i] = nullptr;
    return node;
}

/**
 * @brief Insert a Word object into the Trie
 *
 * @param word  The Word object to be inserted
 * @note If the key of the Word object already exists in the Trie, the Word object will be re-inserted into the Trie
 */
void Trie::insert(Word word)
{
    TrieNode *cur = root;
    for (int i = 0; i < word.getKey().length(); ++i)
    {
        char c = tolower(word.getKey().at(i));
        if (!cur->children[c])
            cur->children[c] = createNode();
        cur = cur->children[c];
    }
    cur->endOfWord = true;
    cur->word      = word;
}

/**
 * @brief Check if a TrieNode is empty
 *
 * @param node The TrieNode to be checked
 * @return true
 * @return false
 */
bool Trie::isEmptyNode(TrieNode *node)
{
    for (int i = 0; i < ALPHABET; ++i)
        if (node->children[i])
            return false;
    return true;
}

/**
 * @brief Remove a Word object from the Trie
 *
 * @param root The root of the Trie
 * @param key The key of the Word object to be removed
 * @param index The index of the key
 * @return TrieNode* The root of the Trie that was modified.
 */
TrieNode *Trie::remove(TrieNode *root, std::string key, int index)
{
    if (!root)
        return nullptr;
    if (index == key.size())
    {
        root->endOfWord = false;
        if (Trie::isEmptyNode(root))
        {
            delete root;
            root = nullptr;
        }
        return root;
    }
    char c            = key.at(index);
    root->children[c] = remove(root->children[c], key, index + 1);
    if (isEmptyNode(root) && root->endOfWord == false)
    {
        delete root;
        root = nullptr;
    }
    return root;
}

/**
 * @brief Clear the Trie
 *
 * @param root The root of the Trie
 */
void Trie::clear(TrieNode *root)
{
    if (!root)
        return;
    for (int i = 0; i < ALPHABET; ++i)
        if (root->children[i])
            clear(root->children[i]);
    delete root;
    root = nullptr;
}

// bool Trie::prefixSearch(std::string key) {
//     TrieNode* cur = root;
//     for (int i = 0; i < key.length(); ++i) {
//         int index = key[i] - 'a';
//         if (cur->children[index] == nullptr)
//             return false;
//         else cur = cur->children[index];
//     }
//     return true;
// }

/**
 * @brief Search for a Word object in the Trie
 *
 * @param key The key of the Word object to be searched
 * @param word The Word object to be returned
 * @return true
 * @return false
 */
bool Trie::search(std::string key, Word &word)
{
    std::transform(key.begin(), key.end(), key.begin(), ::tolower); // convert the input to lowercase letters

    TrieNode *cur = root;
    for (int i = 0; i < key.length(); ++i)
    {
        char c = tolower(key.at(i));
        if (cur->children[c] == nullptr)
            return false;
        else
            cur = cur->children[c];
    }

    if (cur->endOfWord)
    {
        word = cur->word;
        return true;
    }
    return false;
}

/**
 * @brief Convert the deleting key to lowercase letters and call the remove() function
 *
 * @param key The key of the Word object to be removed
 */
void Trie::remove(std::string key)
{
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    remove(root, key, 0);
}

/**
 * @brief Suggest words with a given prefix
 *
 * @param prefix The prefix to be searched
 * @return std::vector<Word> A vector of Word objects that have the given prefix, or an empty vector if no Word object
 * with the given prefix is found.
 */
std::vector<Word> Trie::wordSuggest(std::string prefix)
{
    TrieNode *cur = root;
    std::vector<Word> wordlist;
    std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);
    for (int i = 0; i < prefix.size(); ++i)
    {
        TrieNode *next = cur->children[prefix.at(i)];
        if (!next)
            return wordlist;
        cur = next;
    }
    int limit = 15;
    if (cur->endOfWord)
    {
        wordlist.push_back(cur->word);
        --limit;
    }
    std::queue<TrieNode *> q;
    q.push(cur);
    wordSuggest(wordlist, limit, q);
    return wordlist;
}

/**
 * @brief Suggest words with a given list of words
 *
 * @param wordlist The list of words to be searched
 * @param limit The maximum number of words to be suggested
 * @param q The queue of TrieNode objects to be searched
 */
void Trie::wordSuggest(std::vector<Word> &wordlist, int limit, std::queue<TrieNode *> &q)
{
    while (!q.empty())
    {
        if (!limit)
            break;
        TrieNode *cur = q.front();
        q.pop();
        for (int i = 0; i < ALPHABET && limit && cur; ++i)
        {
            TrieNode *now = cur->children[i];
            if (now)
            {
                if (now->endOfWord)
                {
                    wordlist.push_back(now->word);
                    --limit;
                }
                else
                    q.push(now);
            }
        }
    }
}

/**
 * @brief Serialize the Trie into a file
 *
 * @param root Root of the Trie
 * @param fout The file to be written to
 * @param delimiter The delimiter to be used
 */
void Trie::serialize(TrieNode *root, std::ofstream &fout, char delimiter)
{
    if (root->endOfWord)
    {
        fout << root->word.getKey() << delimiter;
        fout << root->word.getType() << delimiter;
        int defCount = root->word.getDefinitionCount();
        fout << defCount << delimiter;
        for (int i = 0; i < defCount; ++i)
            fout << root->word.getDefinition(i) << delimiter;
    }

    for (int i = 0; i < ALPHABET; ++i)
    {
        if (root->children[i])
            serialize(root->children[i], fout, delimiter);
    }
}

/**
 * @brief Deserialize the Trie from an already built dataset file
 *
 * @param fin The file to be read from
 * @param delimiter The delimiter to be used
 */
void Trie::deserialize(std::ifstream &fin, char delimiter)
{
    int n;
    while (!fin.eof())
    {
        Word word;
        std::string tmp;
        std::getline(fin, tmp, delimiter);
        // std::cout << tmp << ' ';
        word.setKey(tmp);
        std::getline(fin, tmp, delimiter);
        // std::cout << tmp << ' ';
        word.setType(tmp);
        std::getline(fin, tmp, delimiter);
        // std::cout << tmp << '\n';
        if (tmp.empty())
        {
            n = 0;
            break;
        }
        n = std::stoi(tmp);
        for (int i = 0; i < n; ++i)
        {
            std::getline(fin, tmp, delimiter);
            word.addDefinition(tmp);
        }
        if (n != 0)
            insert(word);
    }
}

/**
 * @brief Caller to serialize() function
 *
 * @param path Path to the file to be written to
 * @param delimiter The delimiter to be used
 * @note Different dataset requires different unique character (character that does not exist in the dataset)
 * to be used as delimiter. The caller need to pass that delimiter manually into the function, because the function
 * does not automatically recognize which dataset is used. Delimeter for each dataset is defined in
 * include/dictionary/build.h.
 */
void Trie::serialize(std::string path, char delimiter)
{
    std::ofstream fout(path);
    serialize(root, fout, delimiter);
    fout.close();
}

/**
 * @brief Caller to deserialize() function
 *
 * @param path Path to the file to be read from
 * @param delimiter The delimiter to be used
 */
void Trie::deserialize(std::string path, char delimiter)
{
    std::ifstream fin(path);
    deserialize(fin, delimiter);
    fin.close();
}

/**
 * @brief Caller to clear() function
 *
 */
void Trie::clear()
{
    clear(this->root);
}

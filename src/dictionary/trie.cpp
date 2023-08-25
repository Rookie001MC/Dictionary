#include "dictionary/trie.h"
#include <algorithm>
#include <ctype.h>

Trie::Trie()
{
    init();
}

void Trie::init() {
    this->root      = new TrieNode;
    root->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        root->children[i] = nullptr;
}

Trie::~Trie()
{
    /*      clear();*/
}

TrieNode *Trie::createNode()
{
    TrieNode *node  = new TrieNode;
    node->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        node->children[i] = nullptr;
    return node;
}

// use for both insertion and modification (re-insert the modified Word object)
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

bool Trie::isEmptyNode(TrieNode *node)
{
    for (int i = 0; i < ALPHABET; ++i)
        if (node->children[i])
            return false;
    return true;
}

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

void Trie::remove(std::string key)
{
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    remove(root, key, 0);
}

// return vectors of possible words with given prefix
// return empty vector of words if no word with given prefix found
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

// different dataset requires different unique character (character that does not exist in the dataset)
// to be used as delimiter. the caller need to pass that delimiter manually into the function (the function)
// does not automatically recognize which dataset is used)
// eng-eng: '#
// eng-vie & vie-eng: '#'
void Trie::serialize(std::string path, char delimiter)
{
    std::ofstream fout(path, std::ios::binary);
    serialize(root, fout, delimiter);
    fout.close();
}

void Trie::deserialize(std::string path, char delimiter)
{
    std::ifstream fin(path, std::ios::binary);
    deserialize(fin, delimiter);
    fin.close();
}

void Trie::clear()
{
    clear(this->root);
}

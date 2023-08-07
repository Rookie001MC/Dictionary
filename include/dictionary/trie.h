#ifndef TRIE_H
#define TRIE_H

#include "word.h"
#include <iostream>
#include <string>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

const int ALPHABET = 42;
struct TrieNode
{
    TrieNode *children[ALPHABET];
    bool endOfWord;
    Word word;
};

class Trie
{
  private:
    TrieNode *root = nullptr;
    TrieNode *createNode();
    TrieNode *remove(TrieNode *root, std::string key, int index);
    void clear(TrieNode *root);
    bool isEmptyNode(TrieNode *node);
    void serialize(TrieNode *root, std::ofstream &fout, char delimiter);
    void deserialize(std::ifstream &fin, char delimiter);
    int getIndex(char c);
    void wordSuggest(std::vector<Word> &wordlist, int limit);
  public:
    Trie();
    ~Trie();
    void insert(Word word);
    // bool prefixSearch(std::string key);

    bool search(std::string key, Word &word);
    void remove(std::string key);
    std::vector<Word> wordSuggest(std::string prefix);
    void serialize(std::string path, char delimiter);
    void deserialize(std::string path, char delimiter);
};

#endif

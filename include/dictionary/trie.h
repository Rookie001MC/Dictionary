#ifndef TRIE_H
#define TRIE_H

#include "word.h"
#include <iostream>
#include <string>

const int ALPHABET = 41;
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
    void serialize(TrieNode *root, std::ofstream &fout);
    void deserialize(std::ifstream &fin);

  public:
    Trie();
    ~Trie();
    void insert(Word word);
    // bool prefixSearch(std::string key);
    bool search(std::string key, Word &word);
    void remove(std::string key);
    void serialize(std::string path);
    void deserialize(std::string path);
};

#endif
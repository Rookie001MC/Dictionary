#include <string>
#include "dictionary/word.h"

const int ALPHABET = 26;
struct TrieNode {
    TrieNode* children[ALPHABET];
    bool endOfWord;
    Word word;
};

class Trie {
    private:
        TrieNode* root = nullptr;
        TrieNode* createNode();
        bool isEmpty(TrieNode* node);
        TrieNode* remove(TrieNode* root, std::string key, int index);
        void clear(TrieNode* root);
    public:
        Trie();
        ~Trie();
        void insert(Word word);
        // bool prefixSearch(std::string key);
        bool search(std::string key);
        void remove(std::string key);
};
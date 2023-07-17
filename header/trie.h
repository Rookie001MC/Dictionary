#include <string>

const int ALPHABET = 26;
struct TrieNode {
    TrieNode* children[ALPHABET];
    bool endOfWord;
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
        void insert(std::string key);
        bool prefixSearch(std::string key);
        bool wholeWordSearch(std::string key);
        void remove(std::string key);
};
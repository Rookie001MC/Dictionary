#include "dictionary/trie.h"

Trie::Trie() {
    this->root = new TrieNode;
    root->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        root->children[i] = nullptr; 
}

Trie::~Trie() {
    clear(this->root);
}

TrieNode* Trie::createNode() {
    TrieNode* node = new TrieNode;
    node->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        node->children[i] = nullptr; 
    return node;
}

void Trie::insert(Word word) {
    TrieNode* cur = root;
    for (int i = 0; i < word.getKey().length(); ++i) {
        int index = word.getKey().at(i) - 'a';
        if (!cur->children[index])
            cur->children[index] = createNode();
        cur = cur->children[index];
    }
    cur->endOfWord = true;
    cur->word = word;
}

bool Trie::isEmpty(TrieNode* node) {
    for (int i = 0; i < ALPHABET; ++i)
        if (node->children[i])
            return false;
    return true;
}

TrieNode* Trie::remove(TrieNode* root, std::string key, int index = 0) {
    if (!root) return;
    if (index == key.size()) {
        root->endOfWord = false;
        if (Trie::isEmpty(root)) {
            delete root;
            root = nullptr;
        }
    }
    int idx = key.at(index) - 'a';
    root->children[index] = remove(root->children[index], key, index + 1);
    Trie::remove(root->children[idx], key, index + 1);
    if (isEmpty(root) && root->endOfWord == false) {
        delete root;
        root = nullptr;
    }
    return root;
}

void Trie::clear(TrieNode* root) {
    if (isEmpty(root)) {
        delete root;
        root = nullptr;
    }
    for (int i = 0; i < ALPHABET; ++i)
        if (root->children[i])
            clear(root->children[i]);
    if (isEmpty(root)) {
        delete root;
        root = nullptr;
    }
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

bool Trie::search(std::string key, Word &word) {
    TrieNode* cur = root;
    for (int i = 0; i < key.length(); ++i) {
        int index = key[i] - 'a';
        if (cur->children[index] == nullptr)
            return false;
        else cur = cur->children[index];
    }
    
    if (cur->endOfWord) {
        word = cur->word;
        return true;
    }
    return false;
}

void Trie::remove(std::string key) {
    remove(root, key, 0);
}
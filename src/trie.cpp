#include "../header/trie.h"

TrieNode* Trie::createNode() {
    TrieNode* newNode = new TrieNode;
    newNode->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        newNode->children[i] = nullptr; 
    return newNode;
}

bool Trie::isEmpty(TrieNode* node) {
    for (int i = 0; i < ALPHABET; ++i)
        if (node->children[i])
            return true;
    return false;
}

void Trie::remove(TrieNode* root, std::string key, int index = 0) {
    if (index == key.size()) {
        root->endOfWord = false;
        if (Trie::isEmpty(root)) {
            delete root;
            root = nullptr;
        }
    }
    int idx = key.at(index) - 'a';
    if (!root->children[idx])
        return;
    Trie::remove(root->children[idx], key, index + 1);
    if (isEmpty(root) && root->endOfWord == false) {
        delete root;
        root = nullptr;
    }
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

Trie::Trie() {
    this->root = new TrieNode;
    root->endOfWord = false;
    for (int i = 0; i < ALPHABET; ++i)
        root->children[i] = nullptr; 
}

Trie::~Trie() {
    clear(this->root);
}

void Trie::insert(std::string key) {
    TrieNode* cur = root;
    for (int i = 0; i < key.length(); ++i) {
        int index = key[i] - 97;
        if (cur->children[index] == nullptr) {
            cur->children[index] = createNode();
            cur = cur->children[index];
        }
    }
    cur->endOfWord = true;
}

bool Trie::prefixSearch(std::string key) {
    TrieNode* cur = root;
    for (int i = 0; i < key.length(); ++i) {
        int index = key[i] - 97;
        if (cur->children[index] == nullptr)
            return false;
        else cur = cur->children[index];
    }
    return true;
}

bool Trie::wholeWordSearch(std::string key) {
    TrieNode* cur = root;
    for (int i = 0; i < key.length(); ++i) {
        int index = key[i] - 97;
        if (cur->children[index] == nullptr)
            return false;
        else cur = cur->children[index];
    }
    return (cur->endOfWord) ? true : false;
}

void Trie::remove(std::string key) {
    remove(root, key, 0);
}

void Trie::clear() {
    clear(root);
}
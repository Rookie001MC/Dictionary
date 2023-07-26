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
        char c = word.getKey().at(i);
        int index;
        if (c >= '0' && c <= '9') {
            index = c - '0' + 26;
        }
        else if (c == '\'')
            index = 36;
        else if (c == '/')
            index = 37;
        else if (c == '-')
            index = 38;
        else if (c == ' ')
            index = 39;
        else if (c == '.')
            index = 40;
        else {
            c = tolower(c);
            index = c - 'a';
        }
        if (!cur->children[index])
            cur->children[index] = createNode();
        cur = cur->children[index];
    }
    cur->endOfWord = true;
    cur->word = word;
}

bool Trie::isEmptyNode(TrieNode* node) {
    for (int i = 0; i < ALPHABET; ++i)
        if (node->children[i])
            return false;
    return true;
}

TrieNode* Trie::remove(TrieNode* root, std::string key, int index = 0) {
    if (!root) return nullptr;
    if (index == key.size()) {
        root->endOfWord = false;
        if (Trie::isEmptyNode(root)) {
            delete root;
            root = nullptr;
        }
    }
    int idx = key.at(index) - 'a';
    root->children[index] = remove(root->children[index], key, index + 1);
    Trie::remove(root->children[idx], key, index + 1);
    if (isEmptyNode(root) && root->endOfWord == false) {
        delete root;
        root = nullptr;
    }
    return root;
}

void Trie::clear(TrieNode* root) {
    if (!root) return;
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

void Trie::serialize(TrieNode* root, std::ofstream &fout) {
    if (!root)  return;
    if (root->endOfWord) {
        std::string key = root->word.getKey();
        std::string type = root->word.getType();
        std::vector<std::string> definitions = root->word.getDefinitions();
        int size = key.size();
        std::cout << size << '\n';
        fout.write((char*) &size, sizeof(int));
        fout.write(key.c_str(), size);
        size = type.size();
        std::cout << size << '\n';
        fout.write((char*) &size, sizeof(int));
        fout.write(type.c_str(), size);
        size = definitions.size();
        std::cout << size << '\n';
        fout.write((char*) &size, sizeof(int));
        for (int i = 0; i < definitions.size(); ++i) {
            std::string definition = definitions.at(i);
            size = definition.size();
            std::cout << size << '\n';
            fout.write((char*) &size, sizeof(int));
            fout.write(definition.c_str(), size);
        }
        return;
    }
    for (int i = 0; i < ALPHABET; ++i) {
        if (root->children[i])
            serialize(root->children[i], fout);
    }
}

void Trie::deserialize(std::ifstream &fin) {
    while(!fin.eof()) {
        Word word;
        std::string tmp;
        int size;
        fin.read((char*) size, sizeof(int));
        fin.read((char*) tmp.c_str(), sizeof(size));
        word.setKey(tmp);
        fin.read((char*) size, sizeof(int));
        fin.read((char*) tmp.c_str(), sizeof(size));
        word.setType(tmp);
        int n;
        fin.read((char*) n, sizeof(int));
        for(int i = 0; i < n; ++i) {
            fin.read((char*) size, sizeof(int));
            fin.read((char*) tmp.c_str(), sizeof(size));
            word.addDefinition(tmp);
        }
        insert(word);
    }
}

void Trie::serialize(std::string path) {
    std::ofstream fout(path, std::ios::binary);
    serialize(root, fout);
    fout.close();
}

void Trie::deserialize(std::string path) {
    std::ifstream fin(path, std::ios::binary);
    deserialize(fin);
    fin.close();
}